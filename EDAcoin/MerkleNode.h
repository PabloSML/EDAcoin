#pragma once
#include <string>
#include <vector>
using namespace std;

class MerkleNode {
public:
	MerkleNode(MerkleNode* left = nullptr, MerkleNode* right = nullptr)
	{
		this->left = left;
		this->right = right;
	}
	~MerkleNode(){}

	void setLeft(MerkleNode* left) { this->left = left; }
	MerkleNode* getLeft() const { return left; }
	void setRight(MerkleNode* right) { this->right = right; }
	MerkleNode* getRight() const { return right; }
	
	string getNodeID() const { return nodeID; }
	void setNodeID(string& nodeID) { this->nodeID = nodeID; }

	bool isLeaf() { return (left == nullptr && right == nullptr); }

private:
	MerkleNode* left;
	MerkleNode* right;
	string nodeID;
};

void buildMerkleTree(MerkleNode* root, int currentLevel, int finalLevel, vector<string>& txIDs, int& currentLeaf);