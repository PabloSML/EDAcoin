#pragma once

#include "Block.h"
#include "Node.h"
#include "SPVNode.h"
#include "MerkleNode.h"
#include <nlohmann/json.hpp>
#include <vector>
#include "Definitions.h"

#include "Blockchain_Service.h"

using namespace std;
using json = nlohmann::json;

class SPVNode; // para que compile

class FullNode : public Node {

public:
	FullNode(const char* nodeID) : Node(nodeID, "Full Node") {}
	~FullNode()
	{
		for (MerkleNode* m : merkleTrees)
			destroyMerkleTree(m);
	}

	void recieveBlock(json& jsonBlock);

	void requestLatestHeaders(vector<blockHeader>* dest, string& latestID);
	void requestAllHeaders(vector<blockHeader>* dest);
	unsigned int requestHeaderCount();

	virtual void attachConnection(Node* connection);
	virtual void dettachConnection(Node* connection);

	virtual Node* getFilter(void) { return nullptr; }

	vector<MerkleNode*> get_merkle_trees(void);
	vector<Block> * get_blockChain(void);

	bool transfer(Node& from, Node& to,	double amount);


	void sendInfo2Spv();
private:
	vector<Block> blockChain;
	list<SPVNode*> filters;
	vector<MerkleNode*> merkleTrees;
	
	blockchain_service bc_service;

	void buildTxList(vector<TransactionS>& transactions, json& jsonTxs, unsigned int txsCount);
	void buildMerkleValidationData(MerkleValidationData& dest, MerkleNode* root, string& txID);
};