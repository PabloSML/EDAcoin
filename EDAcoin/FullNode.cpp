#include "FullNode.h"
#include "Crypto.h"

#define NOT_FOUND_INDEX_YET -1


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
	string prevBlockID = jsonBlock[LABEL_BLOCK_PREV_BLOCK_ID].get<string>();

	vector<TransactionS> transactions;
	json jsonTxs = jsonBlock[LABEL_BLOCK_TXS];							//Obtengo las transacciones(json) del bloque(json) ingresado.
	unsigned int txsCount = (unsigned int) jsonTxs.size();				//Guardo la cantidad de transacciones del bloque en una variable temporal.

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

		updateTxList(t);
		update_wallet(t, blockID);
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

vector<json>
FullNode::requestLatestHeaders(string latestID)
{
	bool found = false;
	vector<json> tempVector;
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


		for (ritr; ritr >= blockChain.rbegin(); ritr--)
		{
			blockHeader tempHeader = (*ritr)->getBlockHeader();
			tempVector.push_back(Header2Json(tempHeader));
			if (ritr == blockChain.rbegin())
				break;
		}
	}

	return tempVector;
}

vector<json>
FullNode::requestAllHeaders(void)
{
	vector<json> tempVector;
	for (Model_Block* B : blockChain)
	{
		blockHeader tempHeader = B->getBlockHeader();
		json tempJson = Header2Json(tempHeader);
		tempVector.push_back(tempJson);
	}
	return tempVector;
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
		string spvPublicKey = s->getStringPubKey();
		for (TransactionS& t : allTrans)
		{
			string publicKey = t.PubKey;
			if (publicKey == spvPublicKey)
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
					if (t.outputs[i].publicKey == spvPublicKey)
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

			json jsonMerkle = EdaMerkleBlock2Json(merkleBlock);

			s->notify(jsonMerkle);
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
		tempTx.PubKey = jsonTxs[i][LABEL_TXS_PUBKEY].get<string>();		//Guardo la public key dentro de la estructura de TransactionS.
		tempTx.signature = String2ByteVector(jsonTxs[i][LABEL_TXS_SIGNATURE].get<string>());

		for (unsigned int j = 0; j < inputCount; j++)		//Para cada input, se obtiene el ID del bloque y de la transaccion y se ponen en el vector con todos los inputs.
		{
			InputS tempInput;
			tempInput.blockID = jsonTxs[i][LABEL_TXS_INPUT][j][LABEL_INPUT_BLOCK_ID].get<string>();
			tempInput.txID = jsonTxs[i][LABEL_TXS_INPUT][j][LABEL_INPUT_TX_ID].get<string>();
			tempTx.inputs.push_back(tempInput);
		}
		
		for (unsigned int j = 0; j < outputCount; j++)		//Para cada output, se obtiene el publicKey y el monto y se ponen en el vector con todos los outputs.
		{
			OutputS tempOutput;
			tempOutput.publicKey = jsonTxs[i][LABEL_TXS_OUTPUT][j][LABEL_TXS_PUBKEY].get<string>();
			tempOutput.amount = stoi(jsonTxs[i][LABEL_TXS_OUTPUT][j][LABEL_OUTPUT_AMOUNT].get<string>());
			tempTx.outputs.push_back(tempOutput);
		}

		transactions.push_back(tempTx);
	}
}

void
FullNode::updateTxList(TransactionS& incoming)
{
	bool found = false;
	for (vector<json>::iterator itr = jsonTxs.begin(); itr < jsonTxs.end() && !found; itr++)
	{
		if (incoming.txID == (*itr)[LABEL_TXS_TXID].get<string>())
		{
			found = true;
			jsonTxs.erase(itr);
		}
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
FullNode::flood(void)		
{	
	while (!floodingQueue.empty())
	{
		netPckg temp = floodingQueue.front();
		floodingQueue.pop();

		Node* sender = temp.sender;
		temp.sender = this;

		cout << nodeID << " has flooded " << endl << temp.data << endl << "from " << sender->getNodeID() << endl;

		for (Node* N : connections)
		{
			if ((N->getNodeType() != string("SPV Node")) && (N != sender))
			{
				if (((FullNode*)N)->analizePackage(temp))
					cout << "And " << N->getNodeID() << " accepted" << endl;
			}
		}
	}
}

bool
FullNode::analizePackage(netPckg package)
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
			//validate block
			isPackageNew = true;
			floodingQueue.push(package);
			recieveBlock(package.data);
			sendInfo2Spv();
		}
	}
	
	else if(package.data.contains(LABEL_TXS_TXID))  // es una Tx
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
			//validate tx
			isPackageNew = true;
			floodingQueue.push(package);
			jsonTxs.push_back(package.data);
		}
	}

	return isPackageNew;
}



bool 
FullNode::check_previous(Model_Block * new_block_received)
{
	bool is_previous_ok = true;

	unsigned long index_of_new_block = new_block_received->get_index_in_blockchain();


	if ((this->blockChain).size() -1  < index_of_new_block) //index comienza en 0
	{
		if ((this->blockChain).size() == index_of_new_block )
		{
			string last_block_ID = (this->blockChain)[(this->blockChain).size() - 1]->getBlockID();
			
			if (!(new_block_received->get_previous_blockID() == last_block_ID))
			{
				is_previous_ok = false;
			}
		}
		else
		{
			is_previous_ok = false;
		}
	}

	return is_previous_ok;
}

bool 
FullNode::is_valid_fork(FullNode * sender_node)
{
	unsigned int size_bck = (unsigned int) (this->blockChain).size();

	bool found_match = false; //indicates if theres is a start of fork


	for (unsigned int index_reverse = size_bck - 1; (index_reverse > 0) && !found_match; index_reverse--)
	{
		Model_Block sender_block_i = (*sender_node->get_block_by_index(index_reverse));

		Model_Block mine_block_i = (*this->get_block_by_index(index_reverse));


		if (mine_block_i == sender_block_i)
		{
			found_match = true;
		}
	}

	return found_match;

}


void
FullNode::fix_blockchain(FullNode * sender_node)
{
	unsigned int size_bck = (unsigned int)(this->blockChain).size();

	int index_match = NOT_FOUND_INDEX_YET;

	for (unsigned int index_reverse = size_bck - 1; (index_reverse > 0) && (index_match == NOT_FOUND_INDEX_YET); index_reverse--)
	{
		Model_Block sender_block_i = (*sender_node->get_block_by_index(index_reverse));

		Model_Block mine_block_i = (*this->get_block_by_index(index_reverse));


		if (mine_block_i == sender_block_i)
		{
			index_match = (int)index_reverse;
		}
	}

	if (index_match != NOT_FOUND_INDEX_YET) //tiene una blockchain parcial 
	{
		int size_mine_blckch = (int)(this->blockChain).size();

		while (size_mine_blckch == index_match + 1)
		{
			(this->blockChain).pop_back();
			size_mine_blckch = (int)(this->blockChain).size();
		}

		int size_sender_blckch = (int) sender_node->get_blockChain()->size();

		for (unsigned int index_block = index_match; size_mine_blckch != size_sender_blckch; index_block++)
		{
			(this->blockChain).push_back(sender_node->get_block_by_index(index_block));
		}


	}
	else //blockchain de raiz distintas
	{

		//copio su blockchain

		int size_mine_blckch = (int)(this->blockChain).size();
		
		while (size_mine_blckch == 0)
		{
			(this->blockChain).pop_back();
			size_mine_blckch = (int)(this->blockChain).size();
		}

		int size_sender_blckch = (int)sender_node->get_blockChain()->size();

		for (unsigned int index_block = 0 ; size_mine_blckch != size_sender_blckch; index_block++)
		{
			(this->blockChain).push_back(sender_node->get_block_by_index(index_block));
		}
	}

}



Model_Block* 
FullNode::get_block_by_index(unsigned int index)
{
	return (this->blockChain)[index];
}



bool 
FullNode::validate_tx(TransactionS tx_to_validate)
{

	/* 
	Una transacción es válida cuando:
	*/


	bool is_ok = true;

	UTXO temp;

	double amount_input = 0.0;

	/*
	A. El HashID debe verificar (el HashID de la Tx debe ser igual al calculado por el
	nodo al recibirla).
	*/


	json tx_json = Transactions2Json(tx_to_validate);
	json auxiliar = tx_json;

	string key_wanted = string(LABEL_TXS_TXID);
	tx_json.erase(key_wanted);

	string json_in_string = tx_json.get<string>();
	string hash_id_generate = HashMessage(json_in_string);

	string hash_original = tx_json[key_wanted].get<string>();

	if (hash_original != hash_id_generate)
	{
		is_ok = false;
	}


	if (is_ok)
	{
		/*
		B. La UTXO referenciada en el Input Transaction de la Tx debe pertenecer al
		arreglo de UTXOs o a las transacciones pendientes (esta verificación solo se
		hace en el caso de los nodos Full. Los SPV siguen verificando en su lugar el
		Merkle Path).

		*/


		for (InputS input_i : tx_to_validate.inputs)
		{
			bool found_utxo_input_used = false;

			string in_blck_id = input_i.blockID;
			string in_tx_id = input_i.txID;

			list<UTXO*>::iterator first_list_av_utxo = (this->allAvailableUTXOs).begin();
			list<UTXO*>::iterator last_list_av_utxo = (this->allAvailableUTXOs).begin();

			for (list<UTXO*>::iterator itr = first_list_av_utxo; (itr != last_list_av_utxo) && !found_utxo_input_used; itr++)
			{
				if (((*itr)->get_blockID() == in_blck_id) && ((*itr)->get_txID() == in_tx_id))
				{
					found_utxo_input_used = true;
					amount_input += (*itr)->get_output().amount;
				}
			}

			if (!found_utxo_input_used) //no encontre utxos como entrada
			{
				is_ok = false;
			}

		}


	}


	
	
	if (is_ok)
	{

		/*
		C. La suma de los montos de EDACoin de los UTXOs referenciados en los Input
		Transactions tiene que coincidir con la suma de los montos de EDACoin
		referenciados en los Output Transactions.
		*/

		for (OutputS output_i : tx_to_validate.outputs)
		{
			amount_input -= output_i.amount;
		}

		if (!amount_input)
		{
			is_ok = false;
		}

	}


	if (is_ok)
	{

		/*
		D. Los unlocking scripts referidos en cada Input Transaction deben
		efectivamente desbloquear los UTXO referidos en cada una de ellas (es decir
		la firma debe poder ser validada con la publicKey).
		*/
	
		string input_json = tx_json[LABEL_TXS_INPUT].get<string>();
		string signature_json = tx_json[LABEL_TXS_SIGNATURE].get<string>();

		vector<byte> signature_vbytes = String2ByteVector(signature_json);

		ECDSA<ECP, SHA256>::PublicKey signature = *((ECDSA<ECP, SHA256>::PublicKey *) String2Pointer(signature_json));

		if (!verifySignature(signature, input_json, signature_vbytes))
		{
			is_ok = false;
		}

	}


	return is_ok;

}


bool
FullNode::validate_block(Model_Block * block_to_validate)
{


	/*
	Un bloque (para los nodos Full) o un block header (para los nodos SPV) es válido
	cuando:
	*/

	bool is_ok = true;


	/*
	A. Se verifica que cumple con el challenge.
	*/
	json j = Block2Json(*block_to_validate);
	string str1 = j[LABEL_BLOCK_BLOCK_ID].get<string>();
	j.erase(LABEL_BLOCK_BLOCK_ID);
	string str2 = j.dump();
	if (str1 != HashMessage(str2))
	{
		cout << "Challenge Invalid" << endl;
		return false;
	}





	if (is_ok)
	{
		/*
		B. El previous block hash coincide con el block hash del bloque anterior.
		*/
		unsigned int size_my_bck = (unsigned int)(this->blockChain).size();

		Model_Block * last_block_in_bck = (this->blockChain)[size_my_bck - 1];

		string previous_block_id_mine = last_block_in_bck->getBlockID();
		
		if (previous_block_id_mine != block_to_validate->get_previous_blockID())
		{
			is_ok = false;
		}

	}


	if (is_ok)
	{
		/*
		C. Todas las transacciones son válidas (sólo verificable por los Full y no por los
		SPV).
		*/

		unsigned int txs_count = block_to_validate->getTxsCount();

		for (unsigned int index = 0; (index<txs_count) && (is_ok); index++)
		{
			is_ok = validate_tx(block_to_validate->get_transactions()[index]);
		}


	}

	return is_ok;


}