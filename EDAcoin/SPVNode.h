#pragma once
#include "Node.h"
#include "FullNode.h"
#include "EDAMerkleBlock.h"

class SPVNode : public Node {
public:
	SPVNode() : Node(string("SPV Node")){}
	~SPVNode(){}

	void notify(EDAMerkleBlock merkleBlock);
	void setFullNodeAdress(FullNode* FNAdress);
	void pullHeaderfromFullNode();

	virtual Node* getFilter(void) { return this; }
};
