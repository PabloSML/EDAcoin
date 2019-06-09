#include "Controller_Block.h"
#include <list>
#include "Subject.h"



using namespace std;

Controller_Block::
Controller_Block(Subject* owner) : Controller(owner), myMerkleTreeCtrl(nullptr)
{
	Subject* subj = this->get_subject_attach();
	model = (Model_Block *)subj;
}

Controller_Block::
~Controller_Block()
{
	if (myMerkleTreeCtrl != nullptr)
		delete myMerkleTreeCtrl;
}

void Controller_Block::
parseTimerEvent(EventData * ev) //refresh
{
	if (this->is_subject_attached == true)
	{
		model->ping();
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
	if (isThisMine(ev))
	{

	}
	else  // si el click no fue en la pantalla de blockChain se pasa para adelante
	{
		if (myMerkleTreeCtrl != nullptr)
		{
			myMerkleTreeCtrl->parseMouseEvent(ev);
			if (myMerkleTreeCtrl->shouldModelDie())	// el evento puede haber sido de Close
			{
				model->destroyMerkleTreeModel();
				if (myMerkleTreeCtrl != nullptr)
				{
					delete myMerkleTreeCtrl;
					myMerkleTreeCtrl = nullptr;
				}
			}
		}
	}
}

bool
Controller_Block::isThisMine(EventData* ev)
{
	ALLEGRO_DISPLAY* evDisplay = ev->al_ev->display.source;
	ALLEGRO_DISPLAY* myDisplay = model->getEnviroment();

	if (evDisplay == myDisplay)
		return true;
	else
		return false;
}

void
Controller_Block::createMerkleTreeCtrl(void)
{
	if (myMerkleTreeCtrl == nullptr)
	{
		myMerkleTreeCtrl = new Controller_MerkleTree(model->getMerkleTreeModel());
	}
}