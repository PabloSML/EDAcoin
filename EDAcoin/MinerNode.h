#pragma once

#include "FullNode.h"

class MinerNode : public FullNode
{
public:
	MinerNode(string& newNodeID);
	~MinerNode();

	virtual void recieveBlock(json& jsonBlock);
	virtual bool analizePackage(netPckg package);

	virtual void create_new_mining_block(void);


private:
	Model_Block* miningBlock;

	MerkleNode * mining_tree;
	json		mining_json;

};