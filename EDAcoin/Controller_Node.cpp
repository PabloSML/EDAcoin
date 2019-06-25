#include "Controller_Node.h"
#include "SPVNode.h"
#include "FullNode.h"
#include <math.h>


bool is_amount_valid(string& amount);



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
		myBlockchainCtrl = nullptr;
	}
}

void Controller_Node::parseMouseEvent(EventData * ev)
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

void Controller_Node::parseKeyboardEvent(EventData * ev) {} // nothing

void Controller_Node::parseTimerEvent(EventData * ev)
{
	if (this->is_subject_attached() == true)
	{
		if (model->getNodeType() != string("SPV Node"))
			((FullNode*)model)->flood();
		else
			((SPVNode*)model)->pullHeaderfromFullNode();

		if (myBlockchainCtrl != nullptr)
			myBlockchainCtrl->parseTimerEvent(ev);
	}
}

void
Controller_Node::forwardMouseEvent(EventData* ev)
{
	if (myBlockchainCtrl != nullptr)
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

void
Controller_Node::forwardKeyboardEvent(EventData* ev) {} // nothing

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
	float distance = sqrt(pow((pos.posX+RADIUS - clickPosX), 2) + pow((pos.posY+RADIUS - clickPosY), 2));
	if (distance <= RADIUS)
		return true;
	else
		return false;
}



void 
Controller_Node::parseTransactionEvent(string& to, string& from, string& amount)
{
	if (from == model->getNodeID())
	{
		if (is_amount_valid(amount))
		{
			json new_tx = model->do_transaction(to, stod(amount));

			if (!new_tx.empty())
			{
				netPckg temppck = { new_tx, model };

				if (model->getNodeType() != string("SPV Node"))
				{
					((FullNode*)model)->analizePackage(temppck);
				}
				else
				{
					((SPVNode *)model)->flood(temppck);
				}
			}
		}
	}	
}





bool is_amount_valid(string& amount)
{
	bool possible_amount = false;


	bool is_positive_number = (amount.find_first_not_of("0123456789.") == string::npos);

	size_t apparence_dot = std::count(amount.begin(), amount.end(), '.');



	if ((apparence_dot <= 1) && is_positive_number)
	{
		possible_amount = true;
	}





	return possible_amount;
}
