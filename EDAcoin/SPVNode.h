#pragma once
#include "Node.h"
#include "FullNode.h"
#include "EDAMerkleBlock.h"
#include "Definitions.h"

class SPVNode : public Node {
public:
	SPVNode(string nodeID) : Node(nodeID, string("SPV Node")), blockChainCount(0), blockHeaderCount(0) {}
	~SPVNode(){}

	void notify(EdaMerkleBlockS merkleBlock); // luego recibira un json
	void pullHeaderfromFullNode();

	virtual Node* getFilter(void) { return this; }

private:
	unsigned int blockChainCount;
	unsigned int blockHeaderCount;
	vector<EdaMerkleBlockS> edaMerkleBlockChain;
	vector<blockHeader> blockHeaders;

	void searchAndValidate(blockHeader& headerToValidate);
	void searchAndValidate(EdaMerkleBlockS& blockToValidate);

	bool searchForMatch(blockHeader& headerToValidate, EdaMerkleBlockS* dest);
	bool searchForMatch(EdaMerkleBlockS& blockToValidate, blockHeader* dest);

	void validateTxs(blockHeader& headerToValidate, EdaMerkleBlockS& blockToValidate);
};
