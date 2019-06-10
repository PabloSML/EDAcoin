#include "Controller_Node.h"
#include "SPVNode.h"
#include "FullNode.h"
#include <math.h>

Controller_Node::Controller_Node(Subject* creator):Controller(creator),myBlockchainCtrl(nullptr)
{
	Subject* subj = this->get_subject_attach();
	model = (Node *)subj;
}

Controller_Node::~Controller_Node()
{
	if (myBlockchainCtrl != nullptr)
	{
		delete myBlockchainCtrl;
	}
}

void Controller_Node::parseMouseEvent(EventData * ev)
{
	if (isThisMine(ev))
	{
		if (clickInMe(ev))
		{
			if (model->getNodeID() == "SPV Node")
			{
				((SPVNode*)model)->createBlockChainModel(ev->event_queue);
				createBlockchainCtrl();
			}
			else
			{
				((FullNode*)model)->createBlockChainModel(ev->event_queue);
				createBlockchainCtrl();
			}
		}
	}
	else if (myBlockchainCtrl != nullptr)
	{
		myBlockchainCtrl->parseMouseEvent(ev);
		if (myBlockchainCtrl->shouldModelDie())	// el evento puede haber sido de Close
		{
			model->destroyBlockChainModel();
			if (myBlockchainCtrl != nullptr)
			{
				delete myBlockchainCtrl;
				myBlockchainCtrl = nullptr;
			}
		}
	}
}

void Controller_Node::parseKeyboardEvent(EventData * ev)
{
	//**Nada por ahora
}

void Controller_Node::parseTimerEvent(EventData * ev)
{
	if (this->is_subject_attached() == true)
	{
		model->ping();
		if (myBlockchainCtrl != nullptr)
			myBlockchainCtrl->parseTimerEvent(ev);
	}
}


bool Controller_Node::isThisMine(EventData* ev)
{
	ALLEGRO_DISPLAY* evDisplay = ev->al_ev->mouse.display;
	ALLEGRO_DISPLAY* myDisplay = model->getEnviroment();

	if (evDisplay == myDisplay)
		return true;
	else
		return false;

}
void Controller_Node::createBlockchainCtrl(void)
{
	if (myBlockchainCtrl == nullptr)
	{
		myBlockchainCtrl = new Controller_Blockchain(model->getBlockChainModel());
	}
}
bool Controller_Node::clickInMe(EventData* ev)
{
	pos_t pos = model->getPos();
	int clickPosX = ev->al_ev->mouse.x;
	int clickPosY = ev->al_ev->mouse.y;
	float distance = sqrt(pow((pos.posX - clickPosX), 2) + pow((pos.posY - clickPosY), 2));
	if (distance <= RADIUS)
		return true;
	else
		return false;
}