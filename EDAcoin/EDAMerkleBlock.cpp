#include "EDAMerkleBlock.h"



EDAMerkleBlock::
EDAMerkleBlock(Block& block, string ID_node)
{
	this->cant_transactions = 0;
	
	this->set_transactions(block, ID_node);
	this->set_transactions_ID(block, ID_node);
	this->set_cant_transactions(block, ID_node);
	

}

//destroyers
EDAMerkleBlock::
~EDAMerkleBlock() {}

//getters
unsigned int EDAMerkleBlock::
get_cant_transactions(void) {
	return this->cant_transactions;
}


list<string> EDAMerkleBlock::
get_transactions_ID(void) {
	return this->transactions_ID;
}


list<Transaction> EDAMerkleBlock::
get_transactions(void) {
	return this->transactions;
}


list<unsigned int> EDAMerkleBlock::
get_merkle_path_lenght(void) {
	return this->merkle_path_lenght;
}


list<json> EDAMerkleBlock::
get_merkle_path(void) {
	return this->merkle_path;
}


string EDAMerkleBlock::
get_merkle_block_id(void) {
	return this->merkle_block_id;
}


void EDAMerkleBlock::
set_transactions(Block& block, string ID_node)
{
	unsigned int max_cant = block.getTxsCount();

	for (unsigned int tx = 0; tx < max_cant; tx++)
	{
		Transaction temp_tx = (block.get_transactions())[tx];

		if (temp_tx.does_appear_ID(ID_node))
		{
			(this->transactions).push_back(temp_tx);
		}

	}
}

void EDAMerkleBlock::
set_transactions_ID(Block& block, string ID_node)
{
	unsigned int max_cant = block.getTxsCount();

	for (unsigned int tx = 0; tx < max_cant; tx++)
	{
		Transaction temp_tx = (block.get_transactions())[tx];

		if (temp_tx.does_appear_ID(ID_node))
		{
			(this->transactions_ID).push_back(ID_node);
		}

	}
}

void EDAMerkleBlock::
set_cant_transactions(Block& block, string ID_node)
{
	unsigned int max_cant = block.getTxsCount();

	for (unsigned int tx = 0; tx < max_cant; tx++)
	{
		Transaction temp_tx = (block.get_transactions())[tx];

		if (temp_tx.does_appear_ID(ID_node))
		{
			(this->cant_transactions)++;
		}

	}

}



