#include "MinerNode.h"

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
			isPackageNew = true;
			floodingQueue.push(package);
			recieveBlock(package.data);
			sendInfo2Spv();
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
			if (miningBlock != nullptr && !miningBlock->hasTransactions())	// para la primer tx de todas
			{
				TransactionS tempTx = Json2Transactions(package.data);
				miningBlock->addTransaction(tempTx);
			}
		}
	}

	return isPackageNew;
}

void
MinerNode::recieveBlock(json& jsonBlock)
{
	string blockID = jsonBlock[LABEL_BLOCK_BLOCK_ID].get<string>();		//Obtengo el BlockID(string) del bloque(json) ingresado.

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

	unsigned long numID = stoul(rootID);

	Model_Block* newBlock = new Model_Block(blockID, numID, txsCount, transactions);				//Crea el bloque o lo manda al blockchain.
	blockChain.push_back(newBlock);
}