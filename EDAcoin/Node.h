#pragma once
#include <string>
#include <list>
#include <nlohmann/json.hpp>
#include "MerkleNode.h"
#include "Definitions.h"
#include "Subject.h"

//#include "Blockchain_Message.h"

#include "Model_Blockchain.h"
#include "View_Blockchain.h"
#include "Allegro.h"


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
	~Node() { destroyBlockChainModel(); }

	string getNodeID() const { return nodeID; }
	void setNodeID(string& nodeID) { this->nodeID = nodeID; }

	string getNodeType() const { return nodeType; }
	void setNodeType(string& nodeType) { this->nodeType = nodeType; }

	pos_t getPos(void) const { return pos; }
	void setPos(float newPosX, float newPosY) { pos.posX = newPosX; pos.posY = newPosY; }

	virtual Node* getFilter(void) = 0;

	virtual void attachConnection(Node* connection) { connections.push_back(connection); }
	virtual bool dettachConnection(Node* connection);

	//void push_message(blockchain_message& message);

	virtual void createBlockChainModel(ALLEGRO_EVENT_QUEUE* event_queue) = 0;
	void destroyBlockChainModel(void);

	Model_Blockchain* getBlockChainModel(void);

	virtual void ping(void);

protected:
	string nodeID;
	string nodeType;
	pos_t pos;
	list<Node*> connections;

	Model_Blockchain* myBlockChainModel; // veremos si no es necesario.

	//vector<blockchain_message> buffer_messages;
};
