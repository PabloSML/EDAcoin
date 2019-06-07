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

typedef struct {
	float posX;
	float posY;
}pos_t;

class Node : public Subject{
public:
	Node():nodeType(""),nodeID("") { }
	Node(const char* nodeID, const char* nodeType) { this->nodeID = string(nodeID); this->nodeType = string(nodeType); }
	~Node(){}

	string getNodeID() const { return nodeID; }
	void setNodeID(string& nodeID) { this->nodeID = nodeID; }

	string getNodeType() const { return nodeType; }
	void setNodeType(string& nodeType) { this->nodeType = nodeType; }

	pos_t getPos(void) const { return pos; }
	void setPos(float newPosX, float newPosY) { pos.posX = newPosX; pos.posY = newPosY; }

	virtual Node* getFilter(void) = 0;

	virtual void attachConnection(Node* connection) { connections.push_back(connection); }
	virtual void dettachConnection(Node* connection);

	void push_message(blockchain_message& message);

protected:
	string nodeID;
	string nodeType;
	pos_t pos;
	list<Node*> connections;

	vector<blockchain_message> buffer_messages;
};
