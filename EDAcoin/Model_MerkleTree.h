#pragma once

#include "MerkleNode.h"
#include "Subject.h"
#include "Allegro.h"
#include <vector>

class Model_MerkleTree : public Subject
{
	public:
		Model_MerkleTree();
		Model_MerkleTree(MerkleNode* new_merkle_root);
		~Model_MerkleTree();

		//getters
		MerkleNode * get_merkle_root(void);

		//setters
		void set_merkle_root(MerkleNode * new_merkle_root);

	private:
		MerkleNode * merkle_root;
};