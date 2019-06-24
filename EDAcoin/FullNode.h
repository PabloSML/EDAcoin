#pragma once

#include "Model_Block.h"
#include "Node.h"
#include "SPVNode.h"
#include "MerkleNode.h"
#include <nlohmann/json.hpp>
#include <vector>
#include "Definitions.h"

//#include "Blockchain_Service.h"
#include "Allegro.h"

using namespace std;
using json = nlohmann::json;

class SPVNode; // para que compile

class FullNode : public Node {

public:
	FullNode(string& nodeID) : Node(nodeID, "Full Node") {}
	FullNode(string& nodeID, const char* nodeType) : Node(nodeID, nodeType) {} // para el Minero
	~FullNode()
	{
		for (MerkleNode* M : merkleTrees)
			destroyMerkleTree(M);
		for (Model_Block* B : blockChain)
			delete B;
	}

	void recieveBlock(json& jsonBlock);

	void requestLatestHeaders(vector<blockHeader>* dest, string& latestID);
	void requestAllHeaders(vector<blockHeader>* dest);
	unsigned int requestHeaderCount();

	virtual void attachConnection(Node* connection);
	virtual bool dettachConnection(Node* connection);

	virtual Node* getFilter(void) { return nullptr; }

	vector<MerkleNode*> get_merkle_trees(void);
	vector<Model_Block*> * get_blockChain(void);

	//bool transfer(Node& from, Node& to,	double amount);

	virtual void createBlockChainModel(ALLEGRO_EVENT_QUEUE* event_queue);

	void sendInfo2Spv();
private:
	vector<Model_Block*> blockChain;
	list<SPVNode*> filters;
	vector<MerkleNode*> merkleTrees;
	

	void buildTxList(vector<TransactionS>& transactions, json& jsonTxs, unsigned int txsCount);
	void buildMerkleValidationData(MerkleValidationData& dest, MerkleNode* root, string& txID);
};