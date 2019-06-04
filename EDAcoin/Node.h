#pragma once
#include <string>
#include <list>
#include <nlohmann/json.hpp>
#include "MerkleNode.h"
#include "Definitions.h"
#include "Subject.h"

#include "Blockchain_Message.h"

using namespace std;
using json = nlohmann::json;



class Node : public Subject{
public:
	Node():nodeType(""),nodeID("") { }
	Node(string nodeID, string nodeType) { this->nodeID = nodeID; this->nodeType = nodeType; }
	~Node(){}

	string getNodeID() const { return nodeID; }
	void setNodeID(string& nodeID) { this->nodeID = nodeID; }

	string getNodeType() const { return nodeType; }
	void setNodeType(string& nodeType) { this->nodeType = nodeType; }

	virtual Node* getFilter(void) = 0;

	virtual void attachConnection(Node* connection) { connections.push_back(connection); }
	virtual void dettachConnection(Node* connection);

	//void updateNode(/*evento*/);

	void push_message(blockchain_message& message);

protected:
	string nodeID;
	string nodeType;
	list<Node*> connections;

	vector<blockchain_message> buffer_messages;
};
