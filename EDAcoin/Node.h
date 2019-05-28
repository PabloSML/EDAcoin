#pragma once
#include <string>
#include <list>
#include <nlohmann/json.hpp>
#include "MerkleNode.h"
#include "Definitions.h"
using namespace std;
using json = nlohmann::json;



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
