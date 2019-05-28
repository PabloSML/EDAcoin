#include "FullNode.h"
#include "Labels.h"

void
FullNode::attachConnection(Node* connection)
{
	connections.push_back(connection);		//Pone el puntero al nodo a la lista de conecciones.
	Node* temp = connection->getFilter();	//Pide el filtro al nodo. Si es un fullnode devuelve nullptr, si es un spv node devuelve su direccion.
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
	string blockID = jsonBlock[LABEL_BLOCK_BLOCK_ID].get<string>();		//Obtengo el BlockID(string) del bloque(json) ingresado.

	vector<TransactionS> transactions;
	json jsonTxs = jsonBlock[LABEL_BLOCK_TXS];							//Obtengo las transacciones(json) del bloque(json) ingresado.
	unsigned int txsCount = (unsigned int) jsonTxs.size();				//Guardo la cantidad de transacciones del bloque en una variable temporal.

	buildTxList(transactions, jsonTxs, txsCount);			//Guardo todas las transacciones en el vector de TransactionS.

	vector<string> txIDs;					//Obtengo todos los IDs de las transacciones.
	for (TransactionS t : transactions)
		txIDs.push_back(t.txID);
	int currentLeaf = 0;
	
	MerkleNode* root = new MerkleNode;
	buildMerkleTree(root, 0, log(txsCount) / log(2), txIDs, currentLeaf);		//Se crea el merkle tree.
	string rootID = createNodeID(root);											//Genera el rootID.
	root->setNodeID(rootID);
	merkleTrees.push_back(root);
	
	const unsigned char* tempCStr = (const unsigned char*)rootID.c_str();
	unsigned long numID = generateID(tempCStr);

	Block newBlock(blockID, numID, txsCount, transactions);				//Crea el bloque o lo manda al blockchain.
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


/*Esta funcion guarda en el vector de TransactionS todas las transacciones que estan en el json ingresado*/
void 
FullNode::buildTxList(vector<TransactionS>& transactions, json& jsonTxs, unsigned int& txsCount)
{
	for (unsigned int i = 0; i < txsCount; i++)		//Para cada transaccion se evaluan los inputs y los outputs y se ponen en el vector de TransactionS
	{
		TransactionS tempTx;
		unsigned int inputCount = (unsigned int) jsonTxs[LABEL_TXS_INPUT].size();			//Guardo la cantidad de "inputs" y "outputs" en variables temporales
		unsigned int outputCount = (unsigned int) jsonTxs[LABEL_TXS_OUTPUT].size();

		tempTx.txID = jsonTxs[LABEL_TXS_TXID].get<string>();			//Guardo el ID de la transaccion dentro de la estructura de TransactionS.
		tempTx.txActor = jsonTxs[LABEL_TXS_TXACTOR].get<string>();		//Guardo el nombre del actor dentro de la estructura de TransactionS.

		for (unsigned int j = 0; j < inputCount; j++)		//Para cada input, se obtiene el ID del bloque y de la transaccion y se ponen en el vector con todos los inputs.
		{
			InputS tempInput;
			tempInput.blockID = jsonTxs[LABEL_TXS_INPUT][j][LABEL_INPUT_BLOCK_ID].get<string>();
			tempInput.txID = jsonTxs[LABEL_TXS_INPUT][j][LABEL_INPUT_TX_ID].get<string>();
			tempTx.inputs.push_back(tempInput);
		}
		
		for (unsigned int j = 0; j < outputCount; j++)		//Para cada output, se obtiene el publicID y el monto y se ponen en el vector con todos los outputs.
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