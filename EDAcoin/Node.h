#pragma once
#include <string>
#include <list>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

typedef struct {
	string blockID;
	string txID;
}InputS;

typedef struct {
	string publicID;
	unsigned int amount;
}OutputS;

typedef struct {
	string txID;
	string txActor; // seria el nombre de quien hace la tx. (provisional)
	vector<InputS> inputs;
	vector<OutputS> outputs;
}TransactionS;

/*typedef struct {
	unsigned long merkleRoot;
	string blockID;
	unsigned int txCount;
	vector<TransactionS> transactions;
}BlockS;*/

/*typedef struct {		// estructura de blockHeader por si sirve
	string blockID;
	unsigned long merkleRoot;
}blockHeader;*/

typedef struct {
	unsigned int txCount;
	vector<TransactionS> transactions;
	unsigned int merklePathLen;
	vector<Step> merklePath;
	string blockID;
}EdaMerkleBlockS;

class Node {
public:
	Node() { nodeType = string(""); nodeID = string(""); }
	Node(string nodeID, string nodeType) { this->nodeID = nodeID; this->nodeType = nodeType; }
	~Node(){}

	string getNodeID() const { return nodeID; }
	void setNodeID(string nodeID) { this->nodeID = nodeID; }

	string getNodeType() const { return nodeType; }
	void setNodeType(string nodeType) { this->nodeType = nodeType; }

	virtual Node* getFilter(void) = 0;

	virtual void attachConnection(Node* connection) { connections.push_back(connection); }
	virtual void dettachConnection(Node* connection);

protected:
	string nodeID;
	string nodeType;
	list<Node*> connections;
};
