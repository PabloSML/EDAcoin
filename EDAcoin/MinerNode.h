#pragma once

#include "FullNode.h"

class MinerNode : public FullNode
{
public:
	MinerNode(string& newNodeID) : FullNode(newNodeID, "Miner Node")
	{
		miningBlock = new Model_Block;
	}
	~MinerNode(){}

	virtual bool analizePackage(netPckg package);

private:
	Model_Block* miningBlock;
};