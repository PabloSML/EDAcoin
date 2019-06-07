#include "Model_Block.h"
#include "Labels.h"
#include "Definitions.h"




Model_Block::Model_Block(string& blockID, unsigned long& merkleRoot, unsigned int& txsCount, vector<TransactionS>& transactions) :
	ImageDescriptor(IMAGE_BLOCK_PATH), blockID(blockID), merkleRoot(merkleRoot), txsCount(txsCount), transactions(transactions)
{

	string aux = "Block ID: ";

	this->set_image_name(aux + this->blockID);
	this->pos_x = 0;
	this->pos_y = 0;
	this->width_image = DEFAULT_WIDTH_BLOCK;
	this->width_image = DEFAULT_HEIGTH_BLOCK;


}

Model_Block::Model_Block(void)
{}

Model_Block::~Model_Block(void)
{

}

blockHeader
Model_Block::getBlockHeader(void) const
{
	blockHeader temp;
	temp.blockID = blockID;
	temp.merkleRoot = merkleRoot;
	return temp;

}

string Model_Block::
getBlockID(void) const { return this->blockID; }

unsigned long Model_Block::
getMerkleRoot(void) const { return this->merkleRoot; }

unsigned int Model_Block::
getTxsCount(void) const { return this->txsCount; }

vector<TransactionS> Model_Block::
get_transactions(void) const { return this->transactions; }

unsigned int Model_Block::
get_pos_x(void) { return this->pos_x; }


unsigned int Model_Block::
get_pos_y(void) { return this->pos_y; }


unsigned int Model_Block::
get_size_x(void) { return this->width_image; }


unsigned int Model_Block::
get_size_y(void) { return this->heigth_image; }


void Model_Block::
set_pos_x(unsigned int new_pos_x) { this->pos_x = new_pos_x; }


void Model_Block::
set_pos_y(unsigned int new_pos_y) { this->pos_y = new_pos_y; }


void Model_Block::
set_size_x(unsigned int new_size_x) { this->width_image = new_size_x; }


void Model_Block::
set_size_y(unsigned int new_size_y) { this->heigth_image = new_size_y; }