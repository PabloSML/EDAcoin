#include "Controller_Sim.h"



Controller_Sim::Controller_Sim(Simulation* owner) : Controller(owner)
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
		parseTimerEvent(ev);
		al_set_target_backbuffer(model->getDisplay());
		model->ping();
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
			cout << "Haha tickles" << endl;
			for (Controller_Node* C : nodeControllers)
				C->parseMouseEvent(ev);
			
			controller_transaction_gui->parseMouseEvent(ev);
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
		cout << "Ouch" << endl;
		
		controller_transaction_gui->parseKeyboardEvent(ev);

		/*
		for (Controller_Node* C : nodeControllers)
			C->parseKeyboardEvent(ev);
		*/
	}
	else
	{
		for (Controller_Node* C : nodeControllers)
			C->forwardKeyboardEvent(ev);
		//**llamar a forwardkeyboard de node.
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
