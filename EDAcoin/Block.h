#pragma once
#include <string>
#include <vector>
#include "Transaction.h"
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

/*
typedef struct {		// estructura de blockHeader por si sirve
	string blockID;
	unsigned long merkleRoot;
}blockHeader;
*/

class Block {
public:
	Block(json& jsonBlock);
	~Block(){}

	string getBlockID(void) const;
	unsigned long getMerkleRoot(void) const;
	unsigned int getTxsCount(void) const;
	vector<Transaction> get_transactions(void) const;
	blockHeader getBlockHeader(void) const; // crea una estructura blockHeader y la devuelve en su nombre

private:
	string blockID;
	unsigned long merkleRoot;
	unsigned int txsCount;
	vector<Transaction> transactions;
};