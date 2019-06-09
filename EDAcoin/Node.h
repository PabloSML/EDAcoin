#pragma once
#include <string>
#include <list>
#include <nlohmann/json.hpp>
#include "MerkleNode.h"
#include "Definitions.h"
#include "Subject.h"

#include "Blockchain_Message.h"

#include "Model_Blockchain.h"
#include "View_Blockchain.h"
#include "Allegro.h"

#define RADIUS 10  //**Need to define radios of node

using namespace std;
using json = nlohmann::json;

typedef struct {
	float posX;
	float posY;
}pos_t;

class Node : public Subject{
public:
	Node():nodeType(""),nodeID(""), myBlockChainModel(nullptr) { }
	Node(const char* nodeID, const char* nodeType) { this->nodeID = string(nodeID); this->nodeType = string(nodeType); myBlockChainModel = nullptr; }
	~Node(){}

	string getNodeID() const { return nodeID; }
	void setNodeID(string& nodeID) { this->nodeID = nodeID; }

	string getNodeType() const { return nodeType; }
	void setNodeType(string& nodeType) { this->nodeType = nodeType; }

	pos_t getPos(void) const { return pos; }
	void setPos(float newPosX, float newPosY) { pos.posX = newPosX; pos.posY = newPosY; }

	virtual Node* getFilter(void) = 0;

	virtual void attachConnection(Node* connection) { connections.push_back(connection); }
	virtual bool dettachConnection(Node* connection);

	void push_message(blockchain_message& message);

	virtual void createBlockChainModel(void) = 0;
	void destroyBlockChainModel(void);

	/*
	Controller_BlockChain* createBlockChainController(void);
	void destroyBlockChainController(Controller_BlockChain* target);
	*/

	ALLEGRO_DISPLAY* getEnviroment(void);

	Model_Blockchain* getBlockChainModel(void);

protected:
	string nodeID;
	string nodeType;
	pos_t pos;
	list<Node*> connections;

	Model_Blockchain* myBlockChainModel; // veremos si no es necesario.

	vector<blockchain_message> buffer_messages;

	ALLEGRO_DISPLAY * environment;
};
