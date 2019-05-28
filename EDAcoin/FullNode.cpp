#include "FullNode.h"
#include "Labels.h"

void
FullNode::attachConnection(Node* connection)
{
	connections.push_back(connection);
	Node* temp = connection->getFilter();
	if (temp != nullptr)
		filters.push_back((SPVNode*)connection);
}

void 
FullNode::dettachConnection(Node* connection)
{
	bool done = false;
	list<Node*>::iterator conecItr = connections.begin();
	int size = (int) connections.size();
	for (int i = 0; i < size && !done; i++, conecItr++)
	{
		if (*conecItr == connection)
		{
			connections.erase(conecItr);
			done = true;
		}
	}

	done = false;
	list<SPVNode*>::iterator filterItr = filters.begin();
	size = (int) filters.size();
	for (int i = 0; i < size && !done; i++, filterItr++)
	{
		if (*filterItr == (SPVNode*)connection)
		{
			filters.erase(filterItr);
			done = true;
		}
	}
}

void 
FullNode::recieveBlock(json& jsonBlock)
{
	string blockID = jsonBlock[LABEL_BLOCK_BLOCK_ID].get<string>();

	vector<TransactionS> transactions;
	json jsonTxs = jsonBlock[LABEL_BLOCK_TXS];
	unsigned int txsCount = (unsigned int) jsonTxs.size();

	buildTxList(transactions, jsonTxs, txsCount);

	vector<string> txIDs;
	for (TransactionS t : transactions)
		txIDs.push_back(t.txID);
	int currentLeaf = 0;
	
	MerkleNode* root = new MerkleNode;
	buildMerkleTree(root, 0, log(txsCount) / log(2), txIDs, currentLeaf);
	string rootID = createNodeID(root);
	root->setNodeID(rootID);
	merkleTrees.push_back(root);
	
	const unsigned char* tempCStr = (const unsigned char*)rootID.c_str();
	unsigned long numID = generateID(tempCStr);

	Block newBlock(blockID, numID, txsCount, transactions);

	blockChain.push_back(newBlock);
}
void
FullNode::requestLatestHeader()
{

}

void 
FullNode::requestHeaderCount()
{

}
void 
FullNode::requestHeader(int num)
{

}
void 
FullNode::getNextHeader()
{

}
void
FullNode::sendInfo2Spv()
{
	vector<Block>::iterator bChainItr = blockChain.end();
	bChainItr--;
	vector<MerkleNode*>::iterator mkTreeItr = merkleTrees.end();
	mkTreeItr--;
	MerkleNode* root = *mkTreeItr;
	vector<TransactionS> allTrans = bChainItr->get_transactions();	// obtiene las transacciones del ultimo bloque agregado
	for (SPVNode* s : filters)	//ejecuta el siguiente codigo por cada nodo spv conectado al full
	{
		EdaMerkleBlockS merkleBlock;
		vector<TransactionS> spvTrans;
		string spvID = s->getNodeID();
		for (TransactionS t : allTrans)
		{
			string txActor = t.txActor;
			if (txActor == spvID)
				spvTrans.push_back(t);
			else
			{
				int outputCount = (int) t.outputs.size();
				bool done = false;
				for (int i = 0; i < outputCount && !done; i++)
				{
					if (t.outputs[i].publicID == spvID)
					{
						done = true;
						spvTrans.push_back(t);
					}
				}
			}
		}
		// aca habria que hacer el merkleBlock y mandarlo (ya esta la lista de tx que involucra al spv)
		unsigned int txCount = spvTrans.size();
		if (txCount) // solo notifica al spv si hay txs que le interesen
		{
			string blockID = bChainItr->getBlockID();
			vector<Step> merklePath;
			buildMerklePath(root, spvID, merklePath);
			unsigned int merklePathLen = merklePath.size();

			merkleBlock.txCount = txCount;
			merkleBlock.transactions = spvTrans;
			merkleBlock.merklePathLen = merklePathLen;
			merkleBlock.merklePath = merklePath;
			merkleBlock.blockID = blockID;

			s->notify(merkleBlock);
		}
	}
}

void 
FullNode::buildTxList(vector<TransactionS>& transactions, json& jsonTxs, unsigned int& txsCount)
{
	for (unsigned int i = 0; i < txsCount; i++)
	{
		TransactionS tempTx;
		unsigned int inputCount = (unsigned int) jsonTxs[LABEL_TXS_INPUT].size();
		unsigned int outputCount = (unsigned int) jsonTxs[LABEL_TXS_OUTPUT].size();

		tempTx.txID = jsonTxs[LABEL_TXS_TXID].get<string>();
		tempTx.txActor = jsonTxs[LABEL_TXS_TXACTOR].get<string>();

		for (unsigned int j = 0; j < inputCount; j++)
		{
			InputS tempInput;
			tempInput.blockID = jsonTxs[LABEL_TXS_INPUT][j][LABEL_INPUT_BLOCK_ID].get<string>();
			tempInput.txID = jsonTxs[LABEL_TXS_INPUT][j][LABEL_INPUT_TX_ID].get<string>();
			tempTx.inputs.push_back(tempInput);
		}
		
		for (unsigned int j = 0; j < outputCount; j++)
		{
			OutputS tempOutput;
			tempOutput.publicID = jsonTxs[LABEL_TXS_OUTPUT][j][LABEL_OUTPUT_ID].get<string>();
			tempOutput.amount = stoi(jsonTxs[LABEL_TXS_OUTPUT][j][LABEL_OUTPUT_AMOUNT].get<string>());
			tempTx.outputs.push_back(tempOutput);
		}

		transactions.push_back(tempTx);
	}
}

vector<MerkleNode*> FullNode::get_merkle_trees(void) {
	return this->merkleTrees;
}