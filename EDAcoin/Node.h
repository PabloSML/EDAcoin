#pragma once
#include <string>
#include <list>
using namespace std;

class Node {
public:
	Node() { nodeType = string(""); nodeID = string(""); }
	Node(string nodeType) { this->nodeType = nodeType; }
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
