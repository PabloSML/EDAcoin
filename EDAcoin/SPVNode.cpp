#include "SPVNode.h"
#include "FormatConverter.h"

void 
SPVNode::notify(json jsonMerkle)
{
	EdaMerkleBlockS merkleBlock = Json2EdaMerkleBlock(jsonMerkle);
	string incomingID = merkleBlock.blockID;
	bool found = false;
	for (vector<EdaMerkleBlockS>::reverse_iterator itr = edaMerkleBlockChain.rbegin(); itr < edaMerkleBlockChain.rend() && !found; itr++)
	{
		if (incomingID == itr->blockID)
			found = true;
	}
	
	if (!found)		// si es un nuevo merkleBlock lo sumo a la lista
	{
		searchAndValidate(merkleBlock);
		edaMerkleBlockChain.push_back(merkleBlock);
		blockChainCount++;
	}
}

void
SPVNode::pullHeaderfromFullNode()	// analogamente, luego recibira json
{
	for (Node* n : connections)
	{
		FullNode* tempFull = (FullNode*)n;
		unsigned int fullHeaderCount = tempFull->requestHeaderCount();
		if (fullHeaderCount > blockHeaderCount)
		{
			vector<json> jsonHeaderReceptor;
			vector<blockHeader> headerReceptor;
			if (blockHeaderCount == 0)
			{
				jsonHeaderReceptor = tempFull->requestAllHeaders();
				for (json& J : jsonHeaderReceptor)
					headerReceptor.push_back(Json2Header(J));
			}
			else
			{
				vector<blockHeader>::reverse_iterator itr = blockHeaders.rbegin();	// obtengo un iterador al ultimo header recibido para conseguir su blockID
				string tempBlockID = itr->blockID;
				jsonHeaderReceptor = tempFull->requestLatestHeaders(tempBlockID);	// luego de esta funcion, la conexion con el full deja de ser necesaria y se pasa a procesar lo recibido
				for (json& J : jsonHeaderReceptor)
					headerReceptor.push_back(Json2Header(J));
			}
			for (blockHeader& b : headerReceptor)
			{
				searchAndValidate(b);
				blockHeaders.push_back(b);
				blockHeaderCount++;
			}
		}
	}
}

void
SPVNode::createBlockChainModel(ALLEGRO_EVENT_QUEUE* event_queue)
{
	if (myBlockChainModel == nullptr)
	{
		myBlockChainModel = new Model_Blockchain(event_queue, nodeID);
		myBlockChainModel->set_blockchain(&blockHeaders);
		View_Blockchain* tempView = new View_Blockchain(WIDTH_DEFAULT, HEIGHT_DEFAULT);
		myBlockChainModel->attach(tempView);
	}
}

void
SPVNode::searchAndValidate(blockHeader& headerToValidate)
{
	EdaMerkleBlockS blockReceptor;
	bool found = searchForMatch(headerToValidate, &blockReceptor);
	if(found)
		validateTxs(headerToValidate, blockReceptor);
}

void
SPVNode::searchAndValidate(EdaMerkleBlockS& blockToValidate)
{
	blockHeader* headerReceptor = nullptr;
	bool found = searchForMatch(blockToValidate, headerReceptor);
	if(found)
		validateTxs(*headerReceptor, blockToValidate);
}

bool
SPVNode::searchForMatch(blockHeader& headerToValidate, EdaMerkleBlockS* dest)
{
	bool found = false;
	string blockIDTarget = headerToValidate.blockID;
	vector<EdaMerkleBlockS>::reverse_iterator itr = edaMerkleBlockChain.rbegin();
	for (itr; itr < edaMerkleBlockChain.rend() && !found; itr++)
	{
		if (itr->blockID == blockIDTarget)
		{
			found = true;
		}
	}
	if (found)
	{
		itr--; // se corrige el incremento que sucedera al terminar este ciclo
		*dest = *itr;	
	}

	return found;
}

bool
SPVNode::searchForMatch(EdaMerkleBlockS& blockToValidate, blockHeader* dest)
{
	bool found = false;
	string blockIDTarget = blockToValidate.blockID;
	vector<blockHeader>::reverse_iterator itr = blockHeaders.rbegin();
	for (itr; itr < blockHeaders.rend() && !found; itr++)
	{
		if (itr->blockID == blockIDTarget)
		{
			found = true;
		}
	}
	if (found)
	{
		itr--;
		*dest = *itr;
	}

	return found;
}

void
SPVNode::validateTxs(blockHeader& headerToValidate, EdaMerkleBlockS& blockToValidate)
{
	if (headerToValidate.blockID == blockToValidate.blockID) // validacion redundante
	{
		unsigned long wantedRoot = headerToValidate.merkleRoot;

		vector<MerkleValidationData>::iterator dataItr = blockToValidate.merklePathDataForTxs.begin();
		for (TransactionS& tx : blockToValidate.transactions)
		{
			unsigned long obtainedRoot;
			string ID = tx.txID;	// el ID inicial sera el ID de la transaccion
			string concat;

			for (Step& stp : dataItr->merklePath)
			{
				direction stepDir = stp.getDir();

				if (stepDir == RIGHT)
					concat = ID + stp.getID();
				else if (stepDir == LEFT)
					concat = stp.getID() + ID;

				obtainedRoot = generateID((const unsigned char*)concat.c_str());
				ID = to_string(obtainedRoot);
			}

			if (obtainedRoot == wantedRoot)
				cout << "A transaction has been successfully validated!" << endl;
				// update wallet
			else
				cout << "A transaction validation has returned an error" << endl;

			dataItr++;
		}
	}
	else
	{
		cout << "Validate fun recieved uncoherent data" << endl;
	}
}

void
SPVNode::flood(netPckg package)
{
	for (Node* N : connections)
	{
		if (N->getNodeType() != string("SPV Node"))
		{
			((FullNode*)N)->analizePackage(package);
		}
	}
}