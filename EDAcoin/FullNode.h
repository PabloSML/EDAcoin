#pragma once

#include "Model_Block.h"
#include "Node.h"
#include "SPVNode.h"
#include "MerkleNode.h"
#include <nlohmann/json.hpp>
#include <vector>
#include <queue>
#include "Definitions.h"
#include "Labels.h"
#include "FormatConverter.h"

//#include "Blockchain_Service.h"
#include "Allegro.h"

using namespace std;
using json = nlohmann::json;

class SPVNode; // para que compile

class FullNode : public Node {

public:
	FullNode(string& nodeID) : Node(nodeID, "Full Node") {}
	FullNode(string& nodeID, const char* nodeType) : Node(nodeID, nodeType) {} // para el Minero
	~FullNode()
	{
		for (MerkleNode* M : merkleTrees)
			destroyMerkleTree(M);
		for (Model_Block* B : blockChain)
			delete B;
		for (UTXO* U : allAvailableUTXOs)
			delete U;
	}

	virtual void recieveBlock(json& jsonBlock);

	vector<json> requestLatestHeaders(string latestID);
	vector<json> requestAllHeaders(void);
	unsigned int requestHeaderCount();

	virtual void attachConnection(Node* connection);
	virtual bool dettachConnection(Node* connection);

	virtual Node* getFilter(void) { return nullptr; }

	vector<MerkleNode*> get_merkle_trees(void);
	vector<Model_Block*> * get_blockChain(void);

	virtual bool analizePackage(netPckg package);
	virtual void flood(void);

	virtual void createBlockChainModel(ALLEGRO_EVENT_QUEUE* event_queue);

	void sendInfo2Spv();

protected:

	queue<netPckg> floodingQueue;

	vector<Model_Block*> blockChain;
	list<SPVNode*> filters;
	vector<MerkleNode*> merkleTrees;
	
	vector<json> jsonTxs;
	void updateTxList(TransactionS& incoming);

	list<UTXO*> allAvailableUTXOs;

	void buildTxList(vector<TransactionS>& transactions, json& jsonTxs, unsigned int txsCount);

	bool check_previous(Model_Block * new_block_received);

	void fix_my_blockchain(string & id_sender_node);

	

private:

	void buildMerkleValidationData(MerkleValidationData& dest, MerkleNode* root, string& txID);
};