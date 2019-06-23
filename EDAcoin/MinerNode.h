#pragma once

#include "FullNode.h"

class MinerNode : public FullNode
{
public:
	MinerNode(string& newNodeID) : FullNode(newNodeID, "Miner Node"){}
	~MinerNode(){}
};