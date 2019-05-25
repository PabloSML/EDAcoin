#pragma once

#include <stdlib.h>
#include <string>
#include <list>
#include <iostream>
#include <nlohmann/json.hpp>
#include "Transaction.h"

using json = nlohmann::json;
using namespace std;

class EDAMerkleBlock {
public:
	EDAMerkleBlock();
	~EDAMerkleBlock();

private:
	unsigned int cantTransaction;
	list<string> transactionID;
	list<Transaction> transactions;
	list<unsigned int> merklePathLength;
	list<json> merklePath; 
	string blockID;

};