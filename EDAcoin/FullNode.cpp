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

bool
FullNode::dettachConnection(Node* connection)
{
	bool success = false;
	size_t currentSizeCon = connections.size();
	size_t currentSizeFil = filters.size();

	connections.remove(connection);
	filters.remove((SPVNode*)connection);
	
	if (currentSizeCon - 1 == connections.size() && currentSizeFil - 1 == filters.size())
		success = true;

	return success;
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
	
	unsigned long numID = stoi(rootID);

	Model_Block* newBlock = new Model_Block(blockID, numID, txsCount, transactions);				//Crea el bloque o lo manda al blockchain.
	blockChain.push_back(newBlock);
}

void
FullNode::requestLatestHeaders(vector<blockHeader>* dest, string& latestID)
{
	bool found = false;
	vector<Model_Block*>::reverse_iterator ritr = blockChain.rbegin();
	for (ritr; ritr < blockChain.rend() && !found; ritr++)		// primero se busca el match empezando desde los ultimos headers (si el spv ya esta conectado esto supone el metodo mas eficiente de recorrer el vector).
	{
		if ((*ritr)->getBlockID() == latestID)
		{
			found = true;
		}
	}
	if (found)	// luego de ser encontrado, se llena el vector destino con los headers pedidos
	{
		ritr--;	// se corrige el offset que generara el incremento al terminar el ciclo
		ritr--;	// se vuelve al primer block no conocido (siguiente al conocido)
		//vector<Model_Block*>::iterator itr = ritr.base();
		for (ritr; ritr >= blockChain.rbegin(); ritr--)
		{
			blockHeader tempHeader = (*ritr)->getBlockHeader();
			dest->push_back(tempHeader);
			if (ritr == blockChain.rbegin())
				break;
		}
	}
}

void
FullNode::requestAllHeaders(vector<blockHeader>* dest)
{
	for (Model_Block* B : blockChain)
	{
		blockHeader tempHeader = B->getBlockHeader();
		dest->push_back(tempHeader);
	}
}

unsigned int 
FullNode::requestHeaderCount()
{
	return (unsigned int) blockChain.size();
}


void
FullNode::sendInfo2Spv()
{
	vector<Model_Block*>::reverse_iterator bChainItr = blockChain.rbegin();
	string blockID = (*bChainItr)->getBlockID();
	vector<MerkleNode*>::reverse_iterator mkTreeItr = merkleTrees.rbegin();
	MerkleNode* root = *mkTreeItr;
	vector<TransactionS> allTrans = (*bChainItr)->get_transactions();	// obtiene las transacciones del ultimo bloque agregado
	for (SPVNode* s : filters)	//ejecuta el siguiente codigo por cada nodo spv conectado al full
	{
		EdaMerkleBlockS merkleBlock;
		vector<TransactionS> spvTrans;
		vector<MerkleValidationData> spvMerkleData;
		string spvID = s->getNodeID();
		for (TransactionS& t : allTrans)
		{
			string txActor = t.txActor;
			if (txActor == spvID)
			{
				spvTrans.push_back(t);
				MerkleValidationData tempData;
				buildMerkleValidationData(tempData, root, t.txID);
				spvMerkleData.push_back(tempData);
			}
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
						MerkleValidationData tempData;
						buildMerkleValidationData(tempData, root, t.txID);
						spvMerkleData.push_back(tempData);
					}
				}
			}
		}
		unsigned int txCount = (unsigned int) spvTrans.size();
		if (txCount) // solo notifica al spv si hay txs que le interesen
		{
			

			merkleBlock.txCount = txCount;
			merkleBlock.transactions = spvTrans;
			merkleBlock.merklePathDataForTxs = spvMerkleData;
			merkleBlock.blockID = blockID;

			s->notify(merkleBlock);
		}
	}
}

void
FullNode::createBlockChainModel(ALLEGRO_EVENT_QUEUE* event_queue)
{
	if (myBlockChainModel == nullptr)
	{
		myBlockChainModel = new Model_Blockchain(event_queue, nodeID);
		myBlockChainModel->set_blockchain(&blockChain);
		myBlockChainModel->set_merkle_trees(&merkleTrees);
		
		View_Blockchain* tempView = new View_Blockchain(WIDTH_DEFAULT, HEIGHT_DEFAULT);
		myBlockChainModel->attach(tempView);
	}

	
}

/*Esta funcion guarda en el vector de TransactionS todas las transacciones que estan en el json ingresado*/
void 
FullNode::buildTxList(vector<TransactionS>& transactions, json& jsonTxs, unsigned int txsCount)
{
	for (unsigned int i = 0; i < txsCount; i++)		//Para cada transaccion se evaluan los inputs y los outputs y se ponen en el vector de TransactionS
	{
		TransactionS tempTx;
		unsigned int inputCount = (unsigned int) jsonTxs[i][LABEL_TXS_INPUT].size();			//Guardo la cantidad de "inputs" y "outputs" en variables temporales
		unsigned int outputCount = (unsigned int) jsonTxs[i][LABEL_TXS_OUTPUT].size();

		tempTx.txID = jsonTxs[i][LABEL_TXS_TXID].get<string>();			//Guardo el ID de la transaccion dentro de la estructura de TransactionS.
		tempTx.txActor = jsonTxs[i][LABEL_TXS_TXACTOR].get<string>();		//Guardo el nombre del actor dentro de la estructura de TransactionS.

		for (unsigned int j = 0; j < inputCount; j++)		//Para cada input, se obtiene el ID del bloque y de la transaccion y se ponen en el vector con todos los inputs.
		{
			InputS tempInput;
			tempInput.blockID = jsonTxs[i][LABEL_TXS_INPUT][j][LABEL_INPUT_BLOCK_ID].get<string>();
			tempInput.txID = jsonTxs[i][LABEL_TXS_INPUT][j][LABEL_INPUT_TX_ID].get<string>();
			tempTx.inputs.push_back(tempInput);
		}
		
		for (unsigned int j = 0; j < outputCount; j++)		//Para cada output, se obtiene el publicID y el monto y se ponen en el vector con todos los outputs.
		{
			OutputS tempOutput;
			tempOutput.publicID = jsonTxs[i][LABEL_TXS_OUTPUT][j][LABEL_OUTPUT_ID].get<string>();
			tempOutput.amount = stoi(jsonTxs[i][LABEL_TXS_OUTPUT][j][LABEL_OUTPUT_AMOUNT].get<string>());
			tempTx.outputs.push_back(tempOutput);
		}

		transactions.push_back(tempTx);
	}
}

void FullNode::buildMerkleValidationData(MerkleValidationData& dest, MerkleNode* root, string& txID)
{
	buildMerklePath(root, txID, dest.merklePath);
	dest.merklePathLen = (unsigned int) dest.merklePath.size();
}

vector<MerkleNode*> FullNode::get_merkle_trees(void) {
	return this->merkleTrees;
}

vector<Model_Block*> * FullNode::
get_blockChain(void) {
	return &(this->blockChain);
}


void
FullNode::flood(json package, Node* sender)		
{	
	// aca deberia llamar a una funcion que analize la info, se fije si ya la tiene y si no la guarde y pase a los demas
	for (Node* N : connections)
	{
		if ((N->getNodeType() != string("SPV Node")) && (N != sender))
		{
			N->flood(package, this);
		}
	}
}