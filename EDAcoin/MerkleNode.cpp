#include "MerkleNode.h"

void buildMerkleTree(MerkleNode* root, int currentLevel, int finalLevel, vector<string>& txIDs, int& currentLeaf)
{
	if (root != NULL)
	{
		if (currentLevel == finalLevel)
		{
			root->setNodeID(txIDs[currentLeaf++]);
		}
		else
		{
			MerkleNode* left = new MerkleNode;
			MerkleNode* right = new MerkleNode;
			root->setLeft(left);
			root->setRight(right);
			buildMerkleTree(left, currentLevel + 1, finalLevel, txIDs, currentLeaf);
			buildMerkleTree(right, currentLevel + 1, finalLevel, txIDs, currentLeaf);
		}
	}
}

string createNodeID(MerkleNode* root)
{
	if (root != NULL)
	{
		MerkleNode* left = root->getLeft();
		MerkleNode* right = root->getRight();

		if (left->isLeaf() && right->isLeaf())
		{

		}
	}
}

static unsigned long generateID(unsigned char* str)
{
	unsigned long ID = 0;
	int c;
	while (c = *str++)
		ID = c + (ID << 6) + (ID << 16) - ID;
	return ID;
}