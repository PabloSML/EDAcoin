#pragma once

#include <string>
#include "Definitions.h"
#include "Block.h"

using namespace std;

enum class type_message : unsigned int {
	NEW_TRANSACTION,
	BLOCKCHAIN,
	BLOCKCHAIN_REQUEST
};

class blockchain_message {

public:
	
	

	blockchain_message(void);
	blockchain_message(type_message type);
	blockchain_message(type_message type, string who_send, string detail);
	blockchain_message(type_message type, Block block);
	blockchain_message(type_message type, vector<Block> blockchain);
	blockchain_message(type_message type, TransactionS transaction);
	~blockchain_message();

	//setters
	void set_type_message(type_message type);
	void set_detail(string detail);
	void set_block(Block block);
	void set_transaction(TransactionS transaction);
	void set_blockchain(vector<Block> blockchain);

	//getters
	type_message get_type_message(void) const;
	string get_detail(void) const;
	Block get_block(void) const;
	TransactionS get_transaction(void) const;
	vector<Block> get_blockchain(void) const;

protected:

	string detail;
	type_message type;
	Block block;
	TransactionS transaction;
	vector<Block> blockchain;
	string node_messenger;

};
