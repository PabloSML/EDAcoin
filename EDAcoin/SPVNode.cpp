#include "SPVNode.h"

void 
SPVNode::notify(EdaMerkleBlockS merkleBlock) // luego recibira un json y debera convertirlo a edaMerkleBlock
{
	vector<EdaMerkleBlockS>::reverse_iterator itr = edaMerkleBlockChain.rbegin();
	string incomingLastID = merkleBlock.blockID;
	string currentLastID = itr->blockID;
	if (incomingLastID != currentLastID)		// si es un nuevo merkleBlock lo sumo a la lista
	{
		edaMerkleBlockChain.push_back(merkleBlock);
		blockChainCount++;
	}
}

void
SPVNode::pullHeaderfromFullNode()	// analogamente, luego recibira json
{
	for (Node* n : connections)
	{
		FullNode* tempFull = (FullNode*)n;
		unsigned int fullHeaderCount = tempFull->requestHeaderCount();
		if (fullHeaderCount == blockHeaderCount + 1)
		{
			blockHeader tempHeader = tempFull->requestLatestHeader();
			blockHeaders.push_back(tempHeader);
			blockHeaderCount++;
		}
	}
}