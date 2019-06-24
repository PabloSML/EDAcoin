#include "Node.h"

#include "Labels.h"

#define BLABLA "A" //eliminar luego


using json = nlohmann::json;

Node::Node(void):
	nodeType(""), nodeID(""), myBlockChainModel(nullptr), amount_wallet(0.0), init_ok(false){


	this->mine_UTXOs = new list<UTXO*>;

	if (this->mine_UTXOs != nullptr)
	{
		this->UTXOs_trying_to_use = new list<UTXO*>;
		
		if (this->UTXOs_trying_to_use != nullptr)
		{
			this->init_ok = true;
		}
		else
		{
			delete this->mine_UTXOs;
		}
		
	}

}


Node::Node(string& nodeID, const char* nodeType):
	myBlockChainModel(nullptr), amount_wallet(0.0), init_ok(false) 
{
	
	this->nodeID = nodeID;
	this->nodeType = string(nodeType);

	this->mine_UTXOs = new list<UTXO*>;

	if (this->mine_UTXOs != nullptr)
	{
		this->UTXOs_trying_to_use = new list<UTXO*>;

		if (this->UTXOs_trying_to_use != nullptr)
		{
			this->init_ok = true;
		}
		else
		{
			delete this->mine_UTXOs;
		}

	}

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

		for (UTXO * actual_utxo : (*(this->UTXOs_trying_to_use)))
		{
			delete actual_utxo;
		}

		delete this->UTXOs_trying_to_use;


		init_ok = false;

	}

	
}


string 
Node::getNodeID() const { return nodeID; }

void 
Node::setNodeID(string& nodeID) { this->nodeID = nodeID; }

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
		transaction[LABEL_TXS_TXID] = BLABLA;

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
			transaction.clear;
		}

		

	}




	return transaction;



}

/*


bool
Node::receive_transaction(json& transaction_UTXO, string& actual_blockID)
{
	bool success_create_tx = true;

	size_t size_outputs = transaction_UTXO[LABEL_TXS_OUTPUT][LABEL_OUTPUT_ID].size();
	bool found_me = false;




	unsigned int index;

	for (size_t size = 0; (size < size_outputs) && !found_me; size++)
	{
		if (transaction_UTXO[LABEL_TXS_OUTPUT][size][LABEL_OUTPUT_ID] == this->getNodeID())
		{
			found_me = true;
			index = (unsigned int) size;
		}

	}

	if (found_me)
	{
		UTXO * new_utxo = new UTXO;

		if (new_utxo != nullptr)
		{
			new_utxo->set_reference(actual_blockID, transaction_UTXO[LABEL_TXS_TXID]);

			OutputS new_output;
			new_output.amount = stod((transaction_UTXO[LABEL_TXS_OUTPUT][index][LABEL_OUTPUT_AMOUNT]).get<string>());
			new_output.publicID = this->getNodeID();

			new_utxo->set_output(new_output);

			(this->mine_UTXOs)->push_back(new_utxo);


			this->amount_wallet += new_output.amount;


		}
		else
		{
			success_create_tx = false;
		}



	}
	else
	{
		success_create_tx = false;
	}


	return success_create_tx;



}

*/

double Node::get_amount_wallet(void)
{
	return this->amount_wallet;
}


UTXO *
Node::take_UTXO_unused(void)
{
	UTXO* ret_utxo = nullptr;


	if (!this->UTXOs_trying_to_use->empty())
	{
		ret_utxo = (this->UTXOs_trying_to_use)->back();

		(this->UTXOs_trying_to_use)->pop_back();

		OutputS output_utxo = ret_utxo->get_output();
	}



	return ret_utxo;

}














