#pragma once

#include <string>
#include <vector>
#include "Node.h"
//#include "Transaction.h"
#include <nlohmann/json.hpp>
#include "ImageDescriptor.h"
#include "Definitions.h"

using namespace std;
using json = nlohmann::json;

typedef struct {		// estructura de blockHeader por si sirve
	string blockID;
	unsigned long merkleRoot;
}blockHeader;

class Block : public ImageDescriptor {
public:
	//Block(json& jsonBlock);
	Block(string& blockID, unsigned long& merkleRoot, unsigned int& txsCount, vector<TransactionS>& transactions);
	Block();
	~Block();

	string getBlockID(void) const;
	unsigned long getMerkleRoot(void) const;
	unsigned int getTxsCount(void) const;
	vector<TransactionS> get_transactions(void) const;
	blockHeader getBlockHeader(void) const; // crea una estructura blockHeader y la devuelve en su nombre

private:
	string blockID;
	unsigned long merkleRoot;
	unsigned int txsCount;
	vector<TransactionS> transactions;
};