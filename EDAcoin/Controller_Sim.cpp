#include "Controller_Sim.h"




Controller_Sim::Controller_Sim(Simulation* owner, ALLEGRO_TIMER* newEvTimer, ALLEGRO_TIMER* newNetTimer) : Controller(owner),
evTimer(newEvTimer), netTimer(newNetTimer)
{
	Subject* subj = this->get_subject_attach();
	model = (Simulation *)subj;

	controller_transaction_gui = new Controller_Transaction_GUI(model->get_transaction_interface_gui());

}

Controller_Sim::~Controller_Sim(void)
{
	for (Controller_Node* C : nodeControllers)
		delete C;
	nodeControllers.clear();

	delete this->controller_transaction_gui;
}

void
Controller_Sim::dispatcher(EventData* ev)
{
	if ((ev->al_ev->type == ALLEGRO_EVENT_DISPLAY_CLOSE) || (ev->al_ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN))
	{
		parseMouseEvent(ev);
		al_set_target_backbuffer(model->getDisplay());
		model->ping();
	}
	else if (ev->al_ev->type == ALLEGRO_EVENT_KEY_DOWN)
	{
		parseKeyboardEvent(ev);
		al_set_target_backbuffer(model->getDisplay());
		model->ping();
	}
	else if (ev->al_ev->type == ALLEGRO_EVENT_TIMER)
	{
		if (ev->al_ev->timer.source == evTimer)
		{
			parseTimerEvent(ev);
			al_set_target_backbuffer(model->getDisplay());
			model->ping();
		}
		else if(ev->al_ev->timer.source == netTimer)
		{
			parseNetworkEvent();
		}
	}
}

void
Controller_Sim::addNodeController(Controller_Node* nodeCtrl)
{
	nodeControllers.push_back(nodeCtrl);
}

bool
Controller_Sim::removeNodeController(Controller_Node* nodeCtrl)
{
	bool success = false;
	size_t currentSize = nodeControllers.size();

	delete nodeCtrl;
	nodeControllers.remove(nodeCtrl);

	if (currentSize - 1 == nodeControllers.size())
	{
		success = true;
	}

	return success;
}

void
Controller_Sim::removeAllNodeCtrl(void)
{
	for (Controller_Node* C : nodeControllers)
		delete C;
	nodeControllers.clear();
}

void
Controller_Sim::parseMouseEvent(EventData* ev)
{
	if (isThisMine(ev))
	{
		if (ev->al_ev->type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			model->triggerEnd();
		}
		else
		{
			for (Controller_Node* C : nodeControllers)
				C->parseMouseEvent(ev);
			
			controller_transaction_gui->parseMouseEvent(ev);

			if (model->get_transaction_interface_gui()->is_transaction_waiting())
			{
				this->attend_transaction();

			}
		}
	}
	else 
	{
		for (Controller_Node* C : nodeControllers)
			C->forwardMouseEvent(ev);
	}
}

void
Controller_Sim::parseKeyboardEvent(EventData* ev) // nothing
{
	if (isThisMine(ev))
	{
		controller_transaction_gui->parseKeyboardEvent(ev);
	}
	else
	{
		for (Controller_Node* C : nodeControllers)
			C->forwardKeyboardEvent(ev);
	}

}

void
Controller_Sim::parseTimerEvent(EventData* ev)
{
	if (this->is_subject_attached() == true)
	{
		for (Controller_Node* C : nodeControllers)
			C->parseTimerEvent(ev);

		controller_transaction_gui->parseTimerEvent(ev);

	}
}

void
Controller_Sim::parseNetworkEvent(void)
{
	if (this->is_subject_attached() == true)
	{
		for (Controller_Node* C : nodeControllers)
		{
			C->parseNetworkEvent();
		}
	}
}

bool
Controller_Sim::isThisMine(EventData* ev)
{
	ALLEGRO_DISPLAY* evDisplay = ev->al_ev->display.source;
	ALLEGRO_DISPLAY* mouseDisp = ev->al_ev->mouse.display;
	ALLEGRO_DISPLAY* keyDisp = ev->al_ev->keyboard.display;
	ALLEGRO_DISPLAY* myDisplay = model->getDisplay();

	if ((myDisplay == evDisplay) || (myDisplay == mouseDisp) || (myDisplay == keyDisp))
		return true;
	else
		return false;
}

bool Controller_Sim::shouldModelDie(void)
{
	return model->shouldEnd();
}




void 
Controller_Sim::attend_transaction(void)
{
	string from_node = model->get_transaction_interface_gui()->get_boxtext(TRANS_INTERF_EDITB1_NMBER)->get_actual_text();
	string to_node = model->get_transaction_interface_gui()->get_boxtext(TRANS_INTERF_EDITB2_NMBER)->get_actual_text();
	string amount = model->get_transaction_interface_gui()->get_boxtext(TRANS_INTERF_EDITB3_NMBER)->get_actual_text();


	for (Controller_Node * NC : this->nodeControllers)
	{
		NC->parseTransactionEvent(to_node, from_node, amount);
	}

	model->get_transaction_interface_gui()->attend_transaction();
}




