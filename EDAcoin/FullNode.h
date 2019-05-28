#pragma once
#include "Node.h"
#include "SPVNode.h"
#include "MerkleNode.h"
#include <nlohmann/json.hpp>
#include <vector>
using namespace std;
using json = nlohmann::json;

class SPVNode; // para que compile

class FullNode : public Node {

public:
	FullNode(string nodeID) : Node(nodeID, string("Full Node")) {}
	~FullNode(){}

	void recieveBlock(json& jsonBlock);

	void requestLatestHeader();
	void requestHeaderCount();
	void requestHeader(int num);
	void getNextHeader();

	virtual void attachConnection(Node* connection);
	virtual void dettachConnection(Node* connection);

	virtual Node* getFilter(void) { return nullptr; }

	void sendInfo2Spv();
private:
	list<SPVNode*> filters;
	vector<MerkleNode*> merkleTrees;

	void buildTxList(vector<TransactionS>& transactions, json& jsonTxs, unsigned int& txsCount);
};