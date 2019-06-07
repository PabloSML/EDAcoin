#pragma once

#include <stdlib.h>
#include <string>
#include <list>
#include <iostream>
#include <nlohmann/json.hpp>
#include "Transaction.h"
#include "Model_Block.h"

using json = nlohmann::json;
using namespace std;


class EDAMerkleBlock {
public:
	//builders
	EDAMerkleBlock(Model_Block& block, string ID_node);

	//destroyers
	~EDAMerkleBlock();

	//getters
	unsigned int get_cant_transactions(void);
	list<string> get_transactions_ID(void);
	list<TransactionS> get_transactions(void);
	list<unsigned int> get_merkle_path_lenght(void);
	list<json> get_merkle_path(void);
	string get_merkle_block_id(void);

private:
	void set_transactions(Model_Block& block, string ID_node);
	void set_transactions_ID(Model_Block& block, string ID_node);
	void set_cant_transactions(Model_Block& block, string ID_node);



	unsigned int cant_transactions;
	list<string> transactions_ID;
	list<TransactionS> transactions;
	list<unsigned int> merkle_path_lenght;
	list<json> merkle_path; 
	string merkle_block_id;

};