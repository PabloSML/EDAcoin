#include "Blockchain_Message.h"

blockchain_message::
blockchain_message(void) {
}

blockchain_message::
blockchain_message(type_message type, vector<Model_Block> blockchain) {
	this->type = type;
	this->blockchain = blockchain;
}

blockchain_message::
blockchain_message(type_message type, string who_send, string new_detail) {
	this->type = type;
	this->node_messenger = who_send;
	this->detail = new_detail;
}

blockchain_message::
blockchain_message(type_message type) {
	this->type = type;
}


blockchain_message::
blockchain_message(type_message type, Model_Block block) {
	this->type = type;
	this->block = block;
}

blockchain_message::
blockchain_message(type_message type, TransactionS transaction) {
	this->type = type;
	this->transaction = transaction;
}



blockchain_message::
~blockchain_message() {

}





//getters

void blockchain_message::
set_type_message(type_message type) {
	this->type = type;
}

void blockchain_message::
set_detail(string detail) {
	this->detail = detail;
}

void blockchain_message::
set_block(Model_Block block) {
	this->block = block;
}

void blockchain_message::
set_transaction(TransactionS transaction) {
	this->transaction = transaction;
}

void blockchain_message::
set_blockchain(vector<Model_Block> blockchain) {
	this->blockchain = blockchain;
}

//getters

type_message blockchain_message::
get_type_message(void) const {
	return this->type;
}

string blockchain_message::
get_detail(void) const {
	return this->detail;
}

Model_Block blockchain_message::
get_block(void) const {
	return this->block;
}

TransactionS blockchain_message::
get_transaction(void) const {
	return this->transaction;
}

vector<Model_Block> blockchain_message::
get_blockchain(void) const {
	return this->blockchain;
}

