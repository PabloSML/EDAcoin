#include "MerkleNode.h"

static unsigned long generateID(const unsigned char* str);

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
	string returnStr = string("");
	if (root != NULL)
	{
		MerkleNode* left = root->getLeft();
		MerkleNode* right = root->getRight();

		if (left->isLeaf() && right->isLeaf())
		{
			string tempStrID = left->getNodeID() + right->getNodeID();
			const unsigned char* tempCStrID = (const unsigned char*)tempStrID.c_str();
			unsigned long numID = generateID(tempCStrID);
			returnStr = to_string(numID);
		}
		else
		{
			string leftNodeID = createNodeID(left);
			string rightNodeID = createNodeID(right);
			left->setNodeID(leftNodeID);
			right->setNodeID(rightNodeID);

			string tempStrID = leftNodeID + rightNodeID;
			const unsigned char* tempCStrID = (const unsigned char*)tempStrID.c_str();
			unsigned long numID = generateID(tempCStrID);
			returnStr = to_string(numID);
		}
	}
	return returnStr;
}

unsigned long generateID(const unsigned char* str)
{
	unsigned long ID = 0;
	int c;
	while (c = *str++)
		ID = c + (ID << 6) + (ID << 16) - ID;
	return ID;
}