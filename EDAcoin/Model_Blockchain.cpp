#include "Model_Blockchain.h"
#include "Definitions.h"

#include "Definitions.h"
#include <string>

#include "FullNode.h"
#include "SPVNode.h"

using namespace std;

Model_Blockchain::
Model_Blockchain(Node* creator)
{
	this->cant_board = (unsigned int)((*this->blockchain).size() / MAX_BLOCKS_PER_DISPLAY);	

	if (!((*this->blockchain).size() % MAX_BLOCKS_PER_DISPLAY)) //si la division es exacta
	{
		(this->cant_board)--;
	}

	this->actual_board = 0;
	
	this->owner = creator;
	
	if (creator->getNodeType().compare(TYPE_NAME_FULLNODE) == 0)
	{
		FullNode * aux = (FullNode*) creator;
		this->blockchain = aux->get_blockChain();
		this->merkle_tree = &(aux->get_merkle_trees());

	}
	else if (creator->getNodeType().compare(TYPE_NAME_SPV_NODE) == 0)
	{
		SPVNode * aux = (SPVNode*)creator;
		
		this->merkle_tree = nullptr;

	}
}

Model_Blockchain::
~Model_Blockchain(void)
{

}

//getters

vector<Model_Block> * Model_Blockchain::
get_blockchain(void) { return this->blockchain; }

unsigned int Model_Blockchain::
get_cant_boards(void) { return this->cant_board; }

unsigned int Model_Blockchain::
get_actual_board(void) { return this->actual_board; }



//setters
void Model_Blockchain::
set_blockchain(vector<Model_Block>& new_blockchain) {
	
	this->blockchain = &new_blockchain; 
	
	this->cant_board = (unsigned int)((*this->blockchain).size() / MAX_BLOCKS_PER_DISPLAY);

	if (!((*this->blockchain).size() % MAX_BLOCKS_PER_DISPLAY)) //si la division es exacta
	{
		(this->cant_board)--;
	}

}


void Model_Blockchain::
set_actual_board(unsigned int new_actual_board) { this->actual_board = new_actual_board; }


vector <Model_Block> create_blockchain_spv(vector<blockHeader> * blockheaders)
{
	vector <Model_Block> blockchain_spv;

	unsigned int cant_blocks = (unsigned int) blockheaders->size();

	blockchain_spv.resize((size_t)cant_blocks);

	for (unsigned int i = 0; i < cant_blocks; i++)
	{

	}



}