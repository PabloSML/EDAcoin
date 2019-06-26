#include "Node.h"

#include "Labels.h"

#define BLABLA "A" //eliminar luego


using json = nlohmann::json;

Node::Node(void):
	nodeType(""), nodeID(""), myBlockChainModel(nullptr), amount_wallet(0.0), init_ok(false){


	this->mine_UTXOs = new list<UTXO*>;

	if (this->mine_UTXOs != nullptr)
	{
		this->UTXOs_updated_unsed = new list<UTXO*>;
		
		if (this->UTXOs_updated_unsed != nullptr)
		{
			this->init_ok = true;
		}
		else
		{
			delete this->mine_UTXOs;
		}
		
	}

	this->privateKey = generatePrivKey();
	this->privateKey.MakePublicKey(this->publicKey);
	//aca no hace el hash de nodeID

}


Node::Node(string& nodeID, const char* nodeType):
	myBlockChainModel(nullptr), amount_wallet(0.0), init_ok(false) 
{
	
	this->nodeID = nodeID;
	this->nodeType = string(nodeType);

	this->mine_UTXOs = new list<UTXO*>;

	if (this->mine_UTXOs != nullptr)
	{
		this->UTXOs_updated_unsed = new list<UTXO*>;

		if (this->UTXOs_updated_unsed != nullptr)
		{
			this->init_ok = true;
		}
		else
		{
			delete this->mine_UTXOs;
		}

	}
	this->privateKey = generatePrivKey();
	this->privateKey.MakePublicKey(this->publicKey);
	SHA256 hash;
	string digest;
	StringSource s(nodeID, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));
	this->hashNodeID = digest;

}


Node::
~Node(void)
{
	destroyBlockChainModel();

	if (init_ok)
	{
		for (UTXO * actual_utxo : (*(this->mine_UTXOs)))
		{
			delete actual_utxo;
		}

		delete this->mine_UTXOs;

		delete this->UTXOs_updated_unsed;


		init_ok = false;

	}

	
}


string 
Node::getNodeID() const { return nodeID; }

string
Node::getHashNodeID(void) const
{
	return this->hashNodeID;
}


void 
Node::setNodeID(string& nodeID) 
{ 
	this->nodeID = nodeID;
	SHA256 hash;
	string digest;
	StringSource s(nodeID, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));
	this->hashNodeID = digest;
}

string 
Node::getNodeType() const { return nodeType; }

void 
Node::setNodeType(string& nodeType) { this->nodeType = nodeType; }

pos_t 
Node::getPos(void) const { return pos; }

void 
Node::setPos(float newPosX, float newPosY) { pos.posX = newPosX; pos.posY = newPosY; }

void
Node::attachConnection(Node* connection) { connections.push_back(connection); }

bool
Node::dettachConnection(Node* connection)
{
	bool success = false;
	size_t currentSize = connections.size();

	connections.remove(connection);

	if (currentSize - 1 == connections.size())
		success = true;

	return success;
}

void
Node::destroyBlockChainModel(void)
{
	if (myBlockChainModel != nullptr)
	{
		delete myBlockChainModel;
		myBlockChainModel = nullptr;
	}
}

Model_Blockchain* Node::getBlockChainModel(void)
{
	return myBlockChainModel;
}

void
Node::ping(void)
{
	notifyObservers();
	if (myBlockChainModel != nullptr)
		myBlockChainModel->ping();
}





json Node::
do_transaction(string& to, double amount)
{


	json transaction;

	if (get_amount_wallet() >= amount)
	{

		//aca iria lo del sha256
		transaction[LABEL_TXS_TXID] = to_string(generateID((const unsigned char*)to_string(randDoubleBetween(1, pow(2, 10))).c_str()));

		double money_using = 0.0;


		bool is_utxo_unused = true;

		for (unsigned int i = 0; (money_using < amount)&&(is_utxo_unused); i++)
		{

			UTXO * actual_utxo = this->take_UTXO_unused();

			if (actual_utxo != nullptr)
			{
				transaction[LABEL_TXS_INPUT][i][LABEL_INPUT_BLOCK_ID] = actual_utxo->get_blockID();
				transaction[LABEL_TXS_INPUT][i][LABEL_INPUT_TX_ID] = actual_utxo->get_txID();

				money_using += (actual_utxo->get_output()).amount;

			}
			else
			{
				is_utxo_unused = false;
			}



			//#error no olvide de hacer esto en lo de la validacion de txs
			//delete actual_utxo; //elimino el espacio en memoria guardado para la utxo


		}


		if (is_utxo_unused)
		{
			transaction[LABEL_TXS_OUTPUT][0][LABEL_OUTPUT_ID] = to;
			transaction[LABEL_TXS_OUTPUT][0][LABEL_OUTPUT_AMOUNT] = to_string(amount);

			if (money_using > amount)
			{
				transaction[LABEL_TXS_OUTPUT][1][LABEL_OUTPUT_ID] = this->getNodeID();
				transaction[LABEL_TXS_OUTPUT][1][LABEL_OUTPUT_AMOUNT] = to_string(money_using - amount);

			}

		}
		else //hubo un error en el medio
		{
			transaction.clear();
		}

	}

	return transaction;

}

double Node::get_amount_wallet(void)
{
	return this->amount_wallet;
}





bool 
Node::update_wallet(TransactionS& tx, string& blockID)
{
	//primero veo si tengo que eliminar utxo's, y si use, si son validas

	bool all_ok = true;

	//verifico si es una utxo mia (osea esta en mi lista de utxos) pero fue una de las que
	//use (osea NO esta en mi lista de utxo actualizadas no usadas)


	//en la transaccion soy quien paga?	


	for (InputS in : tx.inputs)
	{
		bool match_utxo = false;

		for (list<UTXO*>::iterator it = (*this->mine_UTXOs).begin(); (it != (*this->mine_UTXOs).end())&&(!match_utxo); ++it) {
			
			if (((*it)->get_blockID() == in.blockID) && ((*it)->get_txID() == in.txID))
			{
				match_utxo = true;

				list<UTXO*> * aux_ptr_list = (this->UTXOs_updated_unsed);

				bool used_tx = true;

				for (list<UTXO*>::iterator it_used = (*aux_ptr_list).begin(); (it_used != (*aux_ptr_list).end())&& used_tx; ++it_used)
				{
					if( ((*it_used)->get_blockID() == in.blockID) && ((*it_used)->get_txID() == in.txID))
					{
						used_tx = false;
					}

				}

				if (used_tx)
				{
					this->amount_wallet -= ((*it)->get_output()).amount; //actualizo mi billetera

					delete (*it);

					(*this->mine_UTXOs).remove(*it);

				}
				else //se encuentra usada y a la vez no
				{
					all_ok = false;
				}
				
			}

		}

	}




	//en la transaccion soy a quien le pagan?

	for (OutputS& out : tx.outputs)
	{
		bool match_utxo = false;

		if (out.publicID == this->getNodeID())
		{
			UTXO * new_utxo = new UTXO;

			new_utxo->set_reference(blockID, tx.txID);
	
			OutputS new_output_utxo = out;
			new_utxo->set_output(new_output_utxo);


			(*this->UTXOs_updated_unsed).push_back(new_utxo);
			(*this->mine_UTXOs).push_back(new_utxo);

			this->amount_wallet += out.amount;

		}
	   
	}

	return all_ok;

}






UTXO *
Node::take_UTXO_unused(void)
{
	UTXO* ret_utxo = nullptr;


	if (!this->UTXOs_updated_unsed->empty())
	{
		ret_utxo = (this->UTXOs_updated_unsed)->back();

		(this->UTXOs_updated_unsed)->pop_back();

	}



	return ret_utxo;

}




