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
	string blockID = string(jsonBlock[LABEL_BLOCK_BLOCK_ID]);

	vector<TransactionS> transactions;
	json jsonTxs = jsonBlock[LABEL_BLOCK_TXS];
	unsigned int txsCount = jsonTxs.size();

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
	vector<TransactionS> allTrans = bChainItr->get_transactions();	// obtiene las transacciones del ultimo bloque agregado
	for (SPVNode* s : filters)
	{
		vector<TransactionS> spvTrans;
		string spvID = s->getNodeID();
		for (TransactionS t : allTrans)
		{
			string txActor = t.txActor;
			if (txActor == spvID)
				spvTrans.push_back(t);
			else
			{
				int outputCount = t.outputs.size();
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
	}
}

void 
FullNode::buildTxList(vector<TransactionS>& transactions, json& jsonTxs, unsigned int& txsCount)
{
	for (unsigned int i = 0; i < txsCount; i++)
	{
		TransactionS tempTx;
		unsigned int inputCount = jsonTxs[LABEL_TXS_INPUT].size();
		unsigned int outputCount = jsonTxs[LABEL_TXS_OUTPUT].size();

		tempTx.txID = string(jsonTxs[LABEL_TXS_TXID]);
		tempTx.txActor = string(jsonTxs[LABEL_TXS_TXACTOR]);

		for (unsigned int j = 0; j < inputCount; j++)
		{
			InputS tempInput;
			tempInput.blockID = string(jsonTxs[LABEL_TXS_INPUT][j][LABEL_INPUT_BLOCK_ID]);
			tempInput.txID = string(jsonTxs[LABEL_TXS_INPUT][j][LABEL_INPUT_TX_ID]);
			tempTx.inputs.push_back(tempInput);
		}
		
		for (unsigned int j = 0; j < outputCount; j++)
		{
			OutputS tempOutput;
			tempOutput.publicID = string(jsonTxs[LABEL_TXS_OUTPUT][j][LABEL_OUTPUT_ID]);
			tempOutput.amount = stoi(string(jsonTxs[LABEL_TXS_OUTPUT][j][LABEL_OUTPUT_AMOUNT]));
			tempTx.outputs.push_back(tempOutput);
		}

		transactions.push_back(tempTx);
	}
}