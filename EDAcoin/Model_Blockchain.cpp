#include "Model_Blockchain.h"
#include "Definitions.h"

#define CANT_TX_SPV	0 //cualquier numero

Model_Blockchain::
Model_Blockchain()
{
	this->cant_board = (unsigned int)(blockchain->size() / MAX_BLOCKS_PER_DISPLAY);	

	if (!(blockchain->size() % MAX_BLOCKS_PER_DISPLAY)) //si la division es exacta
	{
		(this->cant_board)--;
	}

	this->actual_board = 0;
	this->enable_show_merkle_trees = false;
}

Model_Blockchain::
~Model_Blockchain(void)
{

}

//getters

vector<Model_Block>* Model_Blockchain::
get_blockchain(void) { return this->blockchain; }

unsigned int Model_Blockchain::
get_cant_boards(void) { return this->cant_board; }

unsigned int Model_Blockchain::
get_actual_board(void) { return this->actual_board; }

bool Model_Blockchain::
can_show_merkle_trees(void) { return this->enable_show_merkle_trees; }

MerkleNode* Model_Blockchain::getMerkleTree(int index)
{
	return (*merkle_tree)[index];
}

//setters
void Model_Blockchain::
set_blockchain(vector<Model_Block>* new_blockchain) {
	
	this->blockchain = new_blockchain; 
	
	this->cant_board = (unsigned int)(blockchain->size() / MAX_BLOCKS_PER_DISPLAY);

	if (!(blockchain->size() % MAX_BLOCKS_PER_DISPLAY)) //si la division es exacta
	{
		(this->cant_board)--;
	}

	this->enable_show_merkle_trees = true; //si entro en este metodo significa que un full node es el nodo que lo uso

}

void Model_Blockchain::
set_blockchain(vector<blockHeader>* new_blockHeaders)		// hay que ver como manejamos esto
{
	
	
	const size_t size_blockchain = new_blockHeaders->size();

	(this->blockchain)->resize(size_blockchain);

	unsigned int cant_blocks = (unsigned int) size_blockchain;

	for (unsigned int i = 0; i < cant_blocks; i++)
	{
		string str = (*new_blockHeaders)[i].blockID;
		unsigned long merkle_root = (*new_blockHeaders)[i].merkleRoot;
		unsigned int tx_count = 0;
		vector<TransactionS> txs;

		(*this->blockchain)[i] = Model_Block(str, merkle_root, tx_count, txs);
	}


	this->enable_show_merkle_trees = false; //si entro en este metodo significa que un spv node es el nodo que lo uso

}


void Model_Blockchain::
set_actual_board(unsigned int new_actual_board) { this->actual_board = new_actual_board; }


