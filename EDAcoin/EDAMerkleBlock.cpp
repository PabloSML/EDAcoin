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
search_id_and_do_callback(Block& block, string ID_node, callback_void function)
{
	unsigned int max_cant = block.getTxsCount();

	for (unsigned int tx = 0; tx < max_cant; tx++)
	{
		Transaction temp_tx = (block.get_transactions())[tx];

		if (temp_tx.does_appear_ID(ID_node))
		{
			function();
		}

	}
}

void EDAMerkleBlock::
search_id_and_do_callback(Block& block, string ID_node, callback_string function)
{
	unsigned int max_cant = block.getTxsCount();

	for (unsigned int tx = 0; tx < max_cant; tx++)
	{
		Transaction temp_tx = (block.get_transactions())[tx];

		if (temp_tx.does_appear_ID(ID_node))
		{
			function(temp_tx.get_id());
		}

	}
}

void EDAMerkleBlock::
search_id_and_do_callback(Block& block, string ID_node, callback_transaction function)
{
	unsigned int max_cant = block.getTxsCount();

	for (unsigned int tx = 0; tx < max_cant; tx++)
	{
		Transaction temp_tx = (block.get_transactions())[tx];

		if (temp_tx.does_appear_ID(ID_node))
		{
			function(temp_tx);
		}

	}
}


void EDAMerkleBlock::
set_transactions(Block& block, string ID_node)
{
	search_id_and_do_callback(block, ID_node, *(this->push_transaction));
}

void EDAMerkleBlock::
set_transactions_ID(Block& block, string ID_node)
{
	search_id_and_do_callback(block, ID_node, *(this->push_transaction_ID));
}

void EDAMerkleBlock::
set_cant_transactions(Block& block, string ID_node)
{
	search_id_and_do_callback(block, ID_node, *(this->increase_cant_transactions));
}


void EDAMerkleBlock::
increase_cant_transactions(void)
{
	(this->cant_transactions)++;
}

void EDAMerkleBlock::
push_transaction_ID(string ID)
{
	(this->transactions_ID).push_back(ID);
}

void EDAMerkleBlock::
push_transaction(Transaction transaction)
{
	(this->transactions).push_back(transaction);
}
