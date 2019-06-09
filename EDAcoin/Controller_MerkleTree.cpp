#include "Controller_MerkleTree.h"
#include <list>
#include "Subject.h"


using namespace std;

Controller_MerkleTree::
Controller_MerkleTree(Subject* creator) : Controller(creator)
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
parseMouseEvent(EventData * ev)
{
	if (isThisMine(ev))
	{
		if (ev->al_ev->type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			model->triggerEnd();
		}
	}
}

void Controller_MerkleTree::
parseKeyboardEvent(EventData * ev) //nothing
{

}

bool
Controller_MerkleTree::shouldModelDie(void)
{
	return model->shouldEnd();
}


bool 
Controller_MerkleTree::isThisMine(EventData* ev)
{
	ALLEGRO_DISPLAY* evDisplay = ev->al_ev->display.source;
	ALLEGRO_DISPLAY* myDisplay = model->getDisplay();

	if (evDisplay == myDisplay)
		return true;
	else
		return false;
}
