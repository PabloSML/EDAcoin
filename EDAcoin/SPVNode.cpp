#include "SPVNode.h"

void 
SPVNode::notify(EdaMerkleBlockS merkleBlock) // luego recibira un json y debera convertirlo a edaMerkleBlock
{
	string incomingID = merkleBlock.blockID;
	bool found = false;
	for (vector<EdaMerkleBlockS>::reverse_iterator itr = edaMerkleBlockChain.rbegin(); itr < edaMerkleBlockChain.rend() && !found; itr++)
	{
		if (incomingID == itr->blockID)
			found = true;
	}
	
	if (!found)		// si es un nuevo merkleBlock lo sumo a la lista
	{
		searchAndValidate(merkleBlock);
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
		if (fullHeaderCount > blockHeaderCount)
		{
			vector<blockHeader> headerReceptor;
			vector<blockHeader>::reverse_iterator itr = blockHeaders.rbegin();	// obtengo un iterador al ultimo header recibido para conseguir su blockID
			tempFull->requestLatestHeaders(&headerReceptor, itr->blockID);	// luego de esta funcion, la conexion con el full deja de ser necesaria y se pasa a procesar lo recibido
			for (blockHeader b : headerReceptor)
			{
				searchAndValidate(b);
				blockHeaders.push_back(b);
				blockHeaderCount++;
			}
		}
	}
}

void
SPVNode::searchAndValidate(blockHeader& headerToValidate)
{

}

void
SPVNode::searchAndValidate(EdaMerkleBlockS& blockToValidate)
{

}