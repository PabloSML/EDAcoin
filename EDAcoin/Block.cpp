#include "Block.h"
#include "Labels.h"

Block::Block(json& jsonBlock)
{
	blockID = string(jsonBlock[LABEL_BLOCK_BLOCK_ID]);
	merkleRoot = stol(string(jsonBlock[LABEL_BLOCK_MERKLE_ROOT]));
	txsCount = stoi(string(jsonBlock[LABEL_BLOCK_TXS_COUNT]));
	
	for (unsigned int i = 0; i < txsCount; i++)
	{
		Transaction temp(jsonBlock[LABEL_BLOCK_TXS][i]);
		transactions.push_back(temp);
	}
}

blockHeader
Block::getBlockHeader(void) const
{
	blockHeader temp;
	temp.blockID = blockID;
	temp.merkleRoot = merkleRoot;
	return temp;
}