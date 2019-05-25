#pragma once

#include <stdlib.h>
#include <string>
#include <list>
#include <iostream>
using namespace std;

class EDAMerkleBlock {
public:
	EDAMerkleBlock();
	~EDAMerkleBlock();

private:
	unsigned int cantTransaction;
	list<string> transactionID;
	//list<Transaction> transactions;
	list<unsigned int> merklePathLength;
	//necesito una lista de merkle paths. 
	//que seria una lista de arreglos de strings (ID)
	// o de unsigned long pasandolo por generateID()
	list<json> merklePath; 
	string blockID;

};