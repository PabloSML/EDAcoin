#include "Model_MerkleTree.h"

Model_MerkleTree::
Model_MerkleTree() : end(false) {

}

Model_MerkleTree::Model_MerkleTree(MerkleNode* new_merkle_root) : merkle_root(new_merkle_root), end(false)
{

}

Model_MerkleTree::
~Model_MerkleTree() {

}

//getters
MerkleNode * Model_MerkleTree::get_merkle_root(void) { return this->merkle_root; }
ALLEGRO_DISPLAY* Model_MerkleTree::getDisplay(void) { return display; }
bool Model_MerkleTree::shouldEnd(void) { return end; }

//setters
void Model_MerkleTree::
set_merkle_root(MerkleNode * new_merkle_root) { this->merkle_root = new_merkle_root; }
void Model_MerkleTree::triggerEnd(void) { end = true; }