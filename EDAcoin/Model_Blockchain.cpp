#include "Model_Blockchain.h"
#include "Definitions.h"


Model_Blockchain::
Model_Blockchain()
{
	this->cant_board = (unsigned int)(blockchain->size() / MAX_BLOCKS_PER_DISPLAY);	

	if (!(blockchain->size() % MAX_BLOCKS_PER_DISPLAY)) //si la division es exacta
	{
		(this->cant_board)--;
	}

	this->actual_board = 0;
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



//setters
void Model_Blockchain::
set_blockchain(vector<Model_Block>* new_blockchain) {
	
	this->blockchain = new_blockchain; 
	
	this->cant_board = (unsigned int)(blockchain->size() / MAX_BLOCKS_PER_DISPLAY);

	if (!(blockchain->size() % MAX_BLOCKS_PER_DISPLAY)) //si la division es exacta
	{
		(this->cant_board)--;
	}

}

void Model_Blockchain::
set_blockchain(vector<blockHeader>* new_blockHeaders)		// hay que ver como manejamos esto
{

}


void Model_Blockchain::
set_actual_board(unsigned int new_actual_board) { this->actual_board = new_actual_board; }


