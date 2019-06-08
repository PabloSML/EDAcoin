#include "Controller_MerkleTree.h"
#include <list>
#include "Subject.h"
#include "Model_MerkleTree.h"


using namespace std;

Controller_MerkleTree::
Controller_MerkleTree()
{

}

Controller_MerkleTree::
~Controller_MerkleTree()
{

}

void Controller_MerkleTree::
parseTimerEvent(EventData * ev) //refresh
{
	if (this->is_subject_attached == true)
	{
		Subject* subj = this->get_subject_attach();
		Model_MerkleTree * p_merkle_tree = (Model_MerkleTree *)subj;
		p_merkle_tree->ping();
	}
	
}


void Controller_MerkleTree::
parseMouseEvent(EventData * ev) //nothing
{

}

void Controller_MerkleTree::
parseKeyboardEvent(EventData * ev) //nothing
{

}
