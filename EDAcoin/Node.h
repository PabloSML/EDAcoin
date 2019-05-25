#pragma once
#include <string>
#include <list>
using namespace std;

class Node {
public:
	Node() { nodeType = string(""); }
	Node(string nodeType) { this->nodeType = nodeType; }
	~Node(){}

	string getNodeType() const { return nodeType; }
	void setNodeType(string nodeType) { this->nodeType = nodeType; }

protected:
	string nodeType;
	list<Node*> connections;
};
