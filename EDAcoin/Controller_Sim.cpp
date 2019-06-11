#include "Controller_Sim.h"



Controller_Sim::Controller_Sim(Simulation* owner) : Controller(owner)
{
	Subject* subj = this->get_subject_attach();
	model = (Simulation *)subj;
}

Controller_Sim::~Controller_Sim(void)
{
	for (Controller_Node* C : nodeControllers)
		delete C;
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
			cout << "Haha tickes" << endl;
			for (Controller_Node* C : nodeControllers)
				C->parseMouseEvent(ev);
			//**llamar a parseMouseEvent de los edit box.
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
		//**llamar al parseKeyboard de los edit box.
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
	}
}

bool
Controller_Sim::isThisMine(EventData* ev)
{
	ALLEGRO_DISPLAY* evDisplay = ev->al_ev->display.source;
	ALLEGRO_DISPLAY* myDisplay = model->getDisplay();

	if (evDisplay == myDisplay)
		return true;
	else
		return false;
}

bool Controller_Sim::shouldModelDie(void)
{
	return model->shouldEnd();
}
