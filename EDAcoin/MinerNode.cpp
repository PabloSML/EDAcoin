#include "MinerNode.h"
#include "FormatConverter.h"

#define DIFFICULTY 2
#define BYTE_SIZE 8
#define MASK 0x80

MinerNode::MinerNode(string& newNodeID) : FullNode(newNodeID, "Miner Node")
{
	miningBlock = nullptr;
	mining_tree = nullptr;
}


MinerNode::~MinerNode() {

	if (miningBlock != nullptr)
	{
		delete miningBlock;
		miningBlock = nullptr;
	}

	if (mining_tree != nullptr)
	{
		delete mining_tree;
		mining_tree = nullptr;
	}

}



bool
MinerNode::analizePackage(netPckg package)
{
	bool isPackageNew = false;

	if (package.data.contains(LABEL_BLOCK_BLOCK_ID))	// es un Bloque
	{
		bool found = false;
		string newBlockID = package.data[LABEL_BLOCK_BLOCK_ID].get<string>();

		if (!blockChain.empty())
		{
			vector<Model_Block*>::reverse_iterator ritr = blockChain.rbegin();
			for (ritr; ritr < blockChain.rend() && !found; ritr++)
			{
				if (newBlockID == (*ritr)->getBlockID())
				{
					found = true;
				}
			}
		}

		if (!found)
		{
			//if: validacion del bloque recibido -> lo siguiente
			haltMining(); // elimina el bloque que se intentaba minar
			isPackageNew = true;
			floodingQueue.push(package);
			recieveBlock(package.data);
			sendInfo2Spv();
			if(!jsonTxs.empty())
				create_new_mining_block(); // restart mining
		}
	}

	else if (package.data.contains(LABEL_TXS_TXID))  // es una Tx
	{
		bool found = false;
		string newTxID = package.data[LABEL_TXS_TXID].get<string>();

		if (!jsonTxs.empty())
		{
			vector<json>::reverse_iterator ritr2 = jsonTxs.rbegin();
			for (ritr2; ritr2 < jsonTxs.rend() && !found; ritr2++)
			{
				if (newTxID == (*ritr2)[LABEL_TXS_TXID].get<string>())
				{
					found = true;
				}
			}
		}

		if (!found)
		{
			//if: validacion de la tx -> lo siguiente
			isPackageNew = true;
			floodingQueue.push(package);
			jsonTxs.push_back(package.data);
			if (miningBlock == nullptr)	// para la primer tx de todas o si no se creo un block porque no habia txs
			{
				create_new_mining_block();
			}
		}
	}

	return isPackageNew;
}

void
MinerNode::recieveBlock(json& jsonBlock)
{
	string blockID = jsonBlock[LABEL_BLOCK_BLOCK_ID].get<string>();		//Obtengo el BlockID(string) del bloque(json) ingresado.
	string prevBlockID = jsonBlock[LABEL_BLOCK_PREV_BLOCK_ID].get<string>();

	vector<TransactionS> transactions;
	json jsonTxs = jsonBlock[LABEL_BLOCK_TXS];							//Obtengo las transacciones(json) del bloque(json) ingresado.
	unsigned int txsCount = (unsigned int)jsonTxs.size();				//Guardo la cantidad de transacciones del bloque en una variable temporal.

	buildTxList(transactions, jsonTxs, txsCount);			//Guardo todas las transacciones en el vector de TransactionS.

	vector<string> txIDs;					//Obtengo todos los IDs de las transacciones para crear el merkle tree
	for (TransactionS t : transactions)		//Ademas se guardan todas las UTXOs del bloque como disponibles y se eliminan las usadas
	{
		txIDs.push_back(t.txID);

		for (InputS& in : t.inputs)
		{
			for (UTXO* u : allAvailableUTXOs)
			{
				if (in.blockID == u->get_blockID() && in.txID == u->get_txID())
				{
					delete u;
					allAvailableUTXOs.remove(u);
				}
			}
		}

		for (OutputS& out : t.outputs)
		{
			UTXO * new_utxo = new UTXO;

			new_utxo->set_reference(blockID, t.txID);

			OutputS new_output_utxo = out;
			new_utxo->set_output(new_output_utxo);

			allAvailableUTXOs.push_back(new_utxo);
		}
	}

	double test = log2(txsCount);

	while (!(floor(test) == ceil(test)))	// si la cantidad de txs no es potencia de 2
	{
		txIDs.push_back(string("dummy"));
		txsCount++;
		test = log2(txsCount);
	}
	int currentLeaf = 0;

	MerkleNode* root = new MerkleNode;
	buildMerkleTree(root, 0, log(txsCount) / log(2), txIDs, currentLeaf);		//Se crea el merkle tree.
	string rootID = createNodeID(root);											//Genera el rootID.
	root->setNodeID(rootID);
	merkleTrees.push_back(root);

	Model_Block* newBlock = new Model_Block(blockID, rootID, txsCount, transactions);				//Crea el bloque o lo manda al blockchain.
	newBlock->set_previous_blockID(prevBlockID);
	blockChain.push_back(newBlock);
}

void 
MinerNode::create_new_mining_block(void)
{
	this->miningBlock = new Model_Block;

	vector<string> txIDs;

	TransactionS feeTx = createFeeTx();

	miningBlock->addTransaction(feeTx);

	txIDs.push_back(feeTx.txID);

	for (json tx_json : this->jsonTxs) //se agregan todas las tx pendientes a minar y se actualiza el tx_count
	{
		TransactionS new_tx = Json2Transactions(tx_json);

		txIDs.push_back(new_tx.txID);

		(this->miningBlock)->addTransaction(new_tx);

	}

	unsigned int txsCount = this->miningBlock->getTxsCount();
	
	double test = log2(txsCount);

	while (!(floor(test) == ceil(test)))	// si la cantidad de txs no es potencia de 2
	{
		txIDs.push_back(string("dummy"));
		txsCount++;
		test = log2(txsCount);
	}

	int currentLeaf = 0;

	this->mining_tree = new MerkleNode;
	buildMerkleTree(this->mining_tree, 0, log2(txsCount), txIDs, currentLeaf);					//Se crea el merkle tree.
	string rootID = createNodeID(this->mining_tree);											//Genera el rootID.
	(this->mining_tree)->setNodeID(rootID);

	(this->miningBlock)->set_merkle_root(rootID);

	Model_Block * last_block_mined = (this->blockChain)[(this->blockChain).size() - 1];

	string temp_prev_id = last_block_mined->getBlockID();

	(this->miningBlock)->set_previous_blockID(temp_prev_id);

	unsigned long tempNounce = randIntBetween(0, pow(2, 32) - 1);

	miningBlock->set_index_block_in_bchn((unsigned long)blockChain.size());

	miningBlock->setNounce(tempNounce);
}

void
MinerNode::haltMining(void)
{
	if(miningBlock != nullptr)
		delete miningBlock;
	if(mining_tree != nullptr)
		destroyMerkleTree(mining_tree);
	miningBlock = nullptr;
	mining_tree = nullptr;
}

TransactionS
MinerNode::createFeeTx()
{
	TransactionS returnTx;
	InputS tempInput;
	OutputS tempOutput;

	tempInput.blockID = string("");
	tempInput.txID = string("");

	tempOutput.publicKey = Pointer2String(&publicKey);
	tempOutput.amount = FEE;

	returnTx.inputs.push_back(tempInput);
	returnTx.outputs.push_back(tempOutput);
	returnTx.PubKey = Pointer2String(&publicKey);
	vector<byte> emptySignature;
	returnTx.signature = emptySignature;

	string tempTxID = string("");
	string idLabel = string(LABEL_TXS_TXID);
	json tempJsonTx = Transactions2Json(returnTx);
	tempJsonTx.erase(idLabel);
	string tempStringTx = tempJsonTx.dump();

	string actualTxID = HashMessage(tempStringTx);

	returnTx.txID = actualTxID;

	return returnTx;
}

bool
MinerNode::miningAttempt()
{
	bool challengeCompleted = false;


	if (miningBlock != nullptr)
	{
		//cout << "Mining attempt by " << nodeID << endl;
		blockHeader headerForHash = miningBlock->getBlockHeader();
		headerForHash.nounce++; // cambio el nounce para intentar otro hash
		if (headerForHash.nounce > pow(2, 31))
			headerForHash.nounce = 2;
		json jsonHeader2hash = Header2Json(headerForHash);
		string blockIDLabel = string(LABEL_BLOCK_BLOCK_ID);
		jsonHeader2hash.erase(blockIDLabel);
		string stringForHash = jsonHeader2hash.dump();

		string hashAttempt = HashMessage(stringForHash);

		//cout << hashAttempt << "by " << nodeID << endl;

		if(passesChallenge(hashAttempt))
		{
			challengeCompleted = true;
			miningBlock->set_blockID(hashAttempt);
			blockChain.push_back(miningBlock);
			mining_json = Block2Json(*miningBlock);
			netPckg tempPckg = { mining_json, this };
			analizePackage(tempPckg);
			miningBlock = nullptr;
			mining_tree = nullptr;
			create_new_mining_block();
		}
	}

	return challengeCompleted;
}

bool 
MinerNode::passesChallenge(string& hashAttempt)
{
	bool success = true;
	int nullBytes = DIFFICULTY / BYTE_SIZE;
	int nullBits = DIFFICULTY % BYTE_SIZE;

	for (int i = 0; i < nullBytes; i++)
	{
		if (hashAttempt[i] != 0)
			success = false;
	}

	unsigned char tempMask = MASK >> nullBits;

	if (hashAttempt[nullBytes] > tempMask)
		success = false;

	return success;
}