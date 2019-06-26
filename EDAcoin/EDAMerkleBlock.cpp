#include "EDAMerkleBlock.h"

//auxiliar functions
bool does_appear_ID(TransactionS * tx, string ID_node);
bool is_transaction_id(InputS * input, string transaction_id);
bool is_output_id(OutputS * output, string output_id);

EDAMerkleBlock::
EDAMerkleBlock(Model_Block& block, string ID_node)
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


list<TransactionS> EDAMerkleBlock::
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
set_transactions(Model_Block& block, string ID_node)
{
	unsigned int max_cant = block.getTxsCount();

	for (unsigned int tx = 0; tx < max_cant; tx++)
	{
		
		TransactionS temp_tx = (block.get_transactions())[tx];

		if (does_appear_ID(&temp_tx,ID_node))
		{
			(this->transactions).push_back(temp_tx);
		}

	}
}

void EDAMerkleBlock::
set_transactions_ID(Model_Block& block, string ID_node)
{
	unsigned int max_cant = block.getTxsCount();

	for (unsigned int tx = 0; tx < max_cant; tx++)
	{
		TransactionS temp_tx = (block.get_transactions())[tx];

		if (does_appear_ID(&temp_tx,ID_node))
		{
			(this->transactions_ID).push_back(ID_node);
		}

	}
}

void EDAMerkleBlock::
set_cant_transactions(Model_Block& block, string ID_node)
{
	unsigned int max_cant = block.getTxsCount();

	for (unsigned int tx = 0; tx < max_cant; tx++)
	{
		TransactionS temp_tx = (block.get_transactions())[tx];

		if (does_appear_ID(&temp_tx,ID_node))
		{
			(this->cant_transactions)++;
		}

	}

}




bool 
does_appear_ID(TransactionS * tx, string ID_node)
{
	bool appear_ID = false;

	vector<InputS> temp_inputs = tx->inputs;
	vector<OutputS> temp_outputs = tx->outputs;

	unsigned int cant_inputs_tx_i = (unsigned int)temp_inputs.size();
	unsigned int cant_outputs_tx_i = (unsigned int)temp_outputs.size();


	for (unsigned int input = 0; (input < cant_inputs_tx_i) && (!appear_ID); input++)
	{
		if (is_transaction_id(&(temp_inputs[input]), ID_node))
		{
			appear_ID = true;
		}
	}


	for (unsigned int output = 0; (output < cant_outputs_tx_i) && (!appear_ID); output++)
	{
		if (is_output_id(&(temp_outputs[output]),ID_node))
		{
			appear_ID = true;
		}
	}

	return appear_ID;

}

bool
is_transaction_id(InputS * input, string transaction_id)
{
	bool is_id_bool = false;

	if (!((input->blockID).compare(transaction_id)))
	{
		is_id_bool = true;
	}

	return is_id_bool;
}

bool
is_output_id(OutputS * output, string output_id)
{
	bool is_id_bool = false;

	if (!((output->publicKey).compare(output_id)))
	{
		is_id_bool = true;
	}

	return is_id_bool;
}