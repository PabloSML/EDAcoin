#pragma once
#include <string>
#include <list>
#include <nlohmann/json.hpp>
#include "MerkleNode.h"
#include "Definitions.h"
#include "Subject.h"
#include "UTXO.h"


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
	Node();
	Node(string& nodeID, const char* nodeType);
	virtual ~Node();

	string getNodeID() const;
	void setNodeID(string& nodeID);

	string getNodeType() const;
	void setNodeType(string& nodeType);

	pos_t getPos(void) const;
	void setPos(float newPosX, float newPosY);

	virtual Node* getFilter(void) = 0;

	virtual void attachConnection(Node* connection);
	virtual bool dettachConnection(Node* connection);

	virtual void createBlockChainModel(ALLEGRO_EVENT_QUEUE* event_queue) = 0;
	void destroyBlockChainModel(void);

	Model_Blockchain* getBlockChainModel(void);

	virtual void ping(void);

	void flood(json package);
	virtual void flood(json package, Node* sender) = 0;





	json do_transaction(string& from, double amount, string& assing_this_TX_ID);

	bool receive_transaction(json& transaction_UTXO, string& actual_blockID);

	double get_amount_wallet(void);

protected:
	string nodeID;
	string nodeType;
	pos_t pos;
	list<Node*> connections;



	Model_Blockchain* myBlockChainModel;



	list<UTXO*> * mine_UTXOs;
	double amount_wallet;
	bool init_ok;




	private:

	UTXO * take_UTXO_and_update_wallet(void);




};
