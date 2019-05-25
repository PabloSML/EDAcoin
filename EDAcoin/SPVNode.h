#pragma once
#include "Node.h"
#include "FullNode.h"

class SPVNode : public Node {
public:
	SPVNode() : Node(string("SPV Node")){}
	~SPVNode(){}

	void notify(merkleBlock);
	void setFullNodeAdress(FullNode* FNAdress);
	void pullHeaderfromFullNode();
};
