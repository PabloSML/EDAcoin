#include "Controller_Block.h"
#include <list>
#include "Subject.h"
#include "Model_Block.h"


using namespace std;

Controller_Block::
Controller_Block()
{
	
}

Controller_Block::
~Controller_Block()
{

}

void Controller_Block::
parseTimerEvent(EventData * ev) //refresh
{
	if (this->is_subject_attached == true)
	{
		Subject* subj = this->get_subject_attach();
		Model_Block * p_block = (Model_Block *)subj;
		p_block->ping();
	}
}


void Controller_Block::
parseMouseEvent(EventData * ev) //nothing
{

}

void Controller_Block::
parseKeyboardEvent(EventData * ev) //nothing
{

}


void
Controller_Block::recieveMouseEv(EventData* ev, MerkleNode* tree)
{

}