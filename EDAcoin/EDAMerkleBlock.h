#pragma once

#include <stdlib.h>
#include <string>
#include <list>
#include <iostream>
#include <nlohmann/json.hpp>
#include "Transaction.h"
#include "Block.h"

using json = nlohmann::json;
using namespace std;

typedef void(*callback_void)(void);
typedef void(*callback_string)(string);
typedef void(*callback_transaction)(Transaction);

class EDAMerkleBlock {
public:
	//builders
	EDAMerkleBlock(Block& block, string ID_node);

	//destroyers
	~EDAMerkleBlock();

	//getters
	unsigned int get_cant_transactions(void);
	list<string> get_transactions_ID(void);
	list<Transaction> get_transactions(void);
	list<unsigned int> get_merkle_path_lenght(void);
	list<json> get_merkle_path(void);
	string get_merkle_block_id(void);

private:
	void set_transactions(Block& block, string ID_node);
	void set_transactions_ID(Block& block, string ID_node);
	void set_cant_transactions(Block& block, string ID_node);


	void search_id_and_do_callback(Block& block, string ID_node, callback_void function);
	void search_id_and_do_callback(Block& block, string ID_node, callback_string function);
	void search_id_and_do_callback(Block& block, string ID_node, callback_transaction function);
	
	void increase_cant_transactions(void);
	void push_transaction_ID(string ID);
	void push_transaction(Transaction transaction);

	unsigned int cant_transactions;
	list<string> transactions_ID;
	list<Transaction> transactions;
	list<unsigned int> merkle_path_lenght;
	list<json> merkle_path; 
	string merkle_block_id;

};