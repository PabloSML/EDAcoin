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

void destroyMerkleTree(MerkleNode* root)
{
	if (root != NULL)
	{
		if (root->isLeaf())
			delete root;
		else
		{
			MerkleNode* left = root->getLeft();
			MerkleNode* right = root->getRight();

			destroyMerkleTree(left);
			destroyMerkleTree(right);
			delete root;
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

		if (left->isLeaf() && right->isLeaf())		//Si left y right son nodos hoja, se concatenan los IDs y llama a la funcion generate ID. Luego se pasa en numero obtenido a un string.
		{
			string tempStrID = left->getNodeID() + right->getNodeID();
			returnStr = HashMessage(tempStrID);
		}
		else
		{											//En caso contrario, se llama a la funcion en forma recursiva hasta llegar al ultimo nivel donde estan las hojas.
			string leftNodeID = createNodeID(left);
			string rightNodeID = createNodeID(right);
			left->setNodeID(leftNodeID);
			right->setNodeID(rightNodeID);

			string tempStrID = leftNodeID + rightNodeID;
			returnStr = HashMessage(tempStrID);
		}
	}
	return returnStr;
}

bool buildMerklePath(MerkleNode* root, string& txID, vector<Step>& path)
{
	if (root != NULL)
	{
		if (root->isLeaf())
		{
			if (root->getNodeID() == txID)
				return true;
			else
				return false;
		}
		else
		{
			MerkleNode* left = root->getLeft();
			MerkleNode* right = root->getRight();

			bool isLeft = buildMerklePath(left, txID, path);
			bool isRight = buildMerklePath(right, txID, path);

			if (isLeft)
			{
				string tempID = right->getNodeID();
				Step tempStep(tempID, RIGHT);
				path.push_back(tempStep);
			}
			if (isRight)
			{
				string tempID = left->getNodeID();
				Step tempStep(tempID, LEFT);
				path.push_back(tempStep);
			}
			return (isLeft || isRight);
		}
	}
	else
		return false;
}