#include "Block.h"
#include "Labels.h"

/*Block::Block(json& jsonBlock)
{
	blockID = string(jsonBlock[LABEL_BLOCK_BLOCK_ID]);
	merkleRoot = stol(string(jsonBlock[LABEL_BLOCK_MERKLE_ROOT]));
	txsCount = stoi(string(jsonBlock[LABEL_BLOCK_TXS_COUNT]));
	
	for (unsigned int i = 0; i < txsCount; i++)
	{
		Transaction temp(jsonBlock[LABEL_BLOCK_TXS][i]);
		transactions.push_back(temp);
	}
}*/

Block::Block(string& blockID, unsigned long& merkleRoot, unsigned int& txsCount, vector<TransactionS>& transactions)
{
	this->blockID = blockID;
	this->merkleRoot = merkleRoot;
	this->txsCount = txsCount;
	this->transactions = transactions;
}

blockHeader
Block::getBlockHeader(void) const
{
	blockHeader temp;
	temp.blockID = blockID;
	temp.merkleRoot = merkleRoot;
	return temp;
}

string Block::
getBlockID(void) const { return this->blockID; }

unsigned long Block::
getMerkleRoot(void) const { return this->merkleRoot; }

unsigned int Block::
getTxsCount(void) const { return this->txsCount; }

vector<TransactionS> Block::
get_transactions(void) const { return this->transactions; }