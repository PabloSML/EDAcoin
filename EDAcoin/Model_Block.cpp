#include "Model_Block.h"
#include "Labels.h"
#include "Definitions.h"




Model_Block::Model_Block(string& blockID, string& merkleRoot, unsigned int& txsCount, vector<TransactionS>& transactions) :
  blockID(blockID), merkleRoot(merkleRoot), txsCount(txsCount), transactions(transactions), myMerkleTreeModel(nullptr)
{
	this->pos_x = 0;
	this->pos_y = 0;
	this->width_image = DEFAULT_WIDTH_BLOCK;
	this->heigth_image = DEFAULT_HEIGTH_BLOCK;

}

Model_Block::Model_Block(void) : myMerkleTreeModel(nullptr), blockID(""), merkleRoot(""), txsCount(0)
{
	this->pos_x = 0;
	this->pos_y = 0;
	this->width_image = DEFAULT_WIDTH_BLOCK;
	this->heigth_image = DEFAULT_HEIGTH_BLOCK;
}


Model_Block::~Model_Block(void)
{
	destroyMerkleTreeModel();
}

blockHeader
Model_Block::getBlockHeader(void) const
{
	blockHeader temp;
	temp.blockID = blockID;
	temp.prevBlockID = prev_blockID;
	temp.merkleRoot = merkleRoot;
	temp.nounce = nounce;
	temp.index = index_block;
	return temp;

}

string Model_Block::
getBlockID(void) const { return this->blockID; }

string Model_Block::
getMerkleRoot(void) const { return this->merkleRoot; }

unsigned int Model_Block::
getTxsCount(void) const { return this->txsCount; }

vector<TransactionS> Model_Block::
get_transactions(void) const { return this->transactions; }


string
Model_Block::get_previous_blockID(void)
{
	return this->prev_blockID;
}

unsigned long 
Model_Block::get_index_in_blockchain(void) { return this->index_block; }

void
Model_Block::addTransaction(TransactionS& newTX) { transactions.push_back(newTX); txsCount++; }

bool
Model_Block::hasTransactions(void) { return !transactions.empty(); }

unsigned long
Model_Block::getNounce(void) const { return nounce; }

void
Model_Block::setNounce(unsigned long newNounce) { nounce = newNounce; }

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

void
Model_Block::createMerkleTreeModel(MerkleNode* root, ALLEGRO_EVENT_QUEUE* event_queue)
{
	if (myMerkleTreeModel == nullptr)
	{
		myMerkleTreeModel = new Model_MerkleTree(root, event_queue, blockID);
		View_MerkleTree* tempView = new View_MerkleTree(WIDTH_DEFAULT, HEIGHT_DEFAULT);
		myMerkleTreeModel->attach(tempView);
	}
}

void
Model_Block::destroyMerkleTreeModel(void)
{
	if (myMerkleTreeModel != nullptr)
	{
		delete myMerkleTreeModel;
		myMerkleTreeModel = nullptr;
	}
}

Model_MerkleTree*
Model_Block::getMerkleTreeModel()
{
	return myMerkleTreeModel;
}

void Model_Block::setMerkleTreeModel(Model_MerkleTree* m)
{
	this->myMerkleTreeModel = m;
}


void
Model_Block::set_blockID(string& new_blockID) { this->blockID = new_blockID;}



void 
Model_Block::set_merkle_root(string& new_merkle_root)
{
	this->merkleRoot = new_merkle_root;
}

void
Model_Block:: set_previous_blockID(string& new_previous_blockID)
{
	this->prev_blockID = new_previous_blockID;

}

void 
Model_Block::set_index_block_in_bchn(unsigned long new_index) { this->index_block = new_index; }


bool
Model_Block::operator==(Model_Block compare_block)
{
	bool are_the_same = true;

	if (this->getBlockID() != compare_block.getBlockID())
	{
		are_the_same = false;
	}

	return are_the_same;
}

