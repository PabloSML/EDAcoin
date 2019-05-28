#pragma once
#include "Node.h"
#include "FullNode.h"
#include "EDAMerkleBlock.h"
#include "Definitions.h"

class SPVNode : public Node {
public:
	SPVNode(string nodeID) : Node(nodeID, string("SPV Node")){}
	~SPVNode(){}

	void notify(EdaMerkleBlockS merkleBlock); // luego recibira un json
	void pullHeaderfromFullNode();

	virtual Node* getFilter(void) { return this; }
};
