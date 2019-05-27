#include "Input.h"
#include "Labels.h"

//builders
Input::
Input(json json_input) {

	this->block_id = string(json_input[LABEL_INPUT_BLOCK_ID]);
	this->transaction_id = string(json_input[LABEL_INPUT_TX_ID]);

}


//destroyers
Input::
~Input() {
}

//settters
void Input::
set_input(string tx_id, string block_id) {
	set_transaction_id(tx_id);
	set_block_id(block_id);	
}

void Input::
set_transaction_id(string tx_id) {
	this->transaction_id = tx_id;
}

void Input::
set_block_id(string block_id) {
	this->block_id = block_id;
}

//getters
string Input::
get_block_id(void) const{
	return this->block_id;
}

string Input::
get_transaction_id(void) const{
	return this->transaction_id;
}

//others functions
string Input::
body(void) {
	string body = this->block_id + this->transaction_id;
	return body;
}

bool Input::
is_transaction_id(string transaction_id)
{
	bool is_id_bool = false;

	if (!((this->transaction_id).compare(transaction_id)))
	{
		is_id_bool = true;
	}

	return is_id_bool;
}

bool Input::
is_block_id(string block_id)
{
	bool is_id_bool = false;

	if (!((this->block_id).compare(block_id)))
	{
		is_id_bool = true;
	}

	return is_id_bool;
}


//operators
bool Input::
operator==(const Input& compare) {
	return (this->block_id == compare.block_id) && (this->transaction_id == compare.transaction_id);
}


