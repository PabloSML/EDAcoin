#include "Block.h"

Block::Block(json& jsonBlock)
{
	blockID = string(jsonBlock["BlockID"]);
	merkleRoot = stol(string(jsonBlock["MerkleRoot"]));
	txsCount = stoi(string(jsonBlock["TxsCount"]));
	for (unsigned int i = 0; i < txsCount; i++)
	{
		Transaction temp(jsonBlock["Txs"][i]);
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