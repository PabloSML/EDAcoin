#include "Controller_MerkleTree.h"
#include <list>
#include "Subject.h"


using namespace std;

Controller_MerkleTree::
Controller_MerkleTree()
{
	Subject* subj = this->get_subject_attach();
	model = (Model_MerkleTree *)subj;
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
		model->ping();
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
