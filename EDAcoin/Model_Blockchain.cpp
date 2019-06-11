#include "Model_Blockchain.h"
//#include "Definitions.h"
#include <iostream>
#include "View_Block.h"

#define CANT_TX_SPV	0 //cualquier numero

Model_Blockchain::
Model_Blockchain(ALLEGRO_EVENT_QUEUE* event_queue) : blockCount(0), cant_board(0), actual_board(0),
enable_show_merkle_trees(false)
{
	//**
	display = al_create_display(WIDTH_DEFAULT, HEIGHT_DEFAULT);		// Intenta crear display de fallar devuelve NULL
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		init_ok = false;
		return;
	}
	init_ok = true;
	al_clear_to_color(al_map_rgb(255, 255, 255)); //Hace clear del backbuffer del diplay al color RGB 0,0,0 (negro)
	al_register_event_source(event_queue, al_get_display_event_source(display)); //REGISTRAMOS EL DISPLAY
	//**
}

Model_Blockchain::
~Model_Blockchain(void)
{
	if (init_ok == true)
	{
		al_destroy_display(display);
		init_ok = false;
	}
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

bool Model_Blockchain::shouldEnd(void) { return end; }

ALLEGRO_DISPLAY* Model_Blockchain::getDisplay(void) { return display; }

MerkleNode* Model_Blockchain::getMerkleTree(int index)
{
	if (index > merkle_tree->size())
		std::cout << "Tried to get inexisting merkle tree (modelBlockChain)" << std::endl;
	return (*merkle_tree)[index];
}

Model_Block* Model_Blockchain::getBlockbyIndex(unsigned int index)
{
	return &((*blockchain)[index]);
}

unsigned int Model_Blockchain::getBlockCount(void) { return blockCount; }

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

		//**No se deberia hacerse con new?
		(*this->blockchain)[i] = Model_Block(str, merkle_root, tx_count, txs);
	}


	this->enable_show_merkle_trees = false; //si entro en este metodo significa que un spv node es el nodo que lo uso

}

void Model_Blockchain::triggerEnd(void) { end = true; }

void Model_Blockchain::
set_actual_board(unsigned int new_actual_board) { this->actual_board = new_actual_board; }

unsigned int
Model_Blockchain::recountBlocks(void)
{
	unsigned int oldCount = blockCount;
	blockCount = (unsigned int)blockchain->size();

	if (blockCount > oldCount)
	{
		for (unsigned int i = oldCount; i < blockCount; i++)	// se le dan views a los bloques nuevos
		{
			View_Block* tempView = new View_Block;
			(*blockchain)[i].attach(tempView);
		}
	}

	return blockCount - oldCount;
}


bool Model_Blockchain::isInitOk(void)
{
	return init_ok;
}
