#pragma once
#include "Node.h"
#include "FullNode.h"
#include "EDAMerkleBlock.h"

class SPVNode : public Node {
public:
	SPVNode(string nodeID) : Node(nodeID, string("SPV Node")){}
	~SPVNode(){}

	void notify(EDAMerkleBlock merkleBlock);
	void pullHeaderfromFullNode();

	virtual Node* getFilter(void) { return this; }
};
