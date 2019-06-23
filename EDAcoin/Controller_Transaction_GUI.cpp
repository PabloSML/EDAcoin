#include "Controller_Transaction_GUI.h"

#include "Definitions.h"



Controller_Transaction_GUI::Controller_Transaction_GUI(Model_Transaction_GUI* owner) : Controller(owner)
{
	Subject* subj = this->get_subject_attach();
	model = (Model_Transaction_GUI *)subj;

	for (unsigned int i = 0; i < model->get_cant_boxttexts(); i++)
	{
		Controller_BoxText * temp_controller = new Controller_BoxText(model->get_boxtext(i));
		(this->edittexts_controllers).push_back(temp_controller);
	}

	for (unsigned int i = 0; i < model->get_cant_pushbuttons(); i++)
	{
		Controller_PushButton * temp_controller = new Controller_PushButton(model->get_pushbutton(i));
		(this->pushButtons_controllers).push_back(temp_controller);
	}
}

Controller_Transaction_GUI::~Controller_Transaction_GUI(void)
{
	for (Controller_PushButton* C : pushButtons_controllers)
		delete C;


	for (Controller_BoxText * edit_text_contr : edittexts_controllers)
		delete edit_text_contr;

}

void
Controller_Transaction_GUI::parseMouseEvent(EventData* ev)
{
	for (int i = 0; i < (int)pushButtons_controllers.size(); i++)
	{
		pushButtons_controllers[i]->parseMouseEvent(ev);
	}

	for (int i = 0; i < (int)edittexts_controllers.size(); i++)
	{
		edittexts_controllers[i]->parseMouseEvent(ev);
	}


	
}

void
Controller_Transaction_GUI::parseKeyboardEvent(EventData* ev) // nothing
{
	for (int i = 0; i < (int)edittexts_controllers.size(); i++)
	{
		edittexts_controllers[i]->parseKeyboardEvent(ev);
	}


}

void
Controller_Transaction_GUI::parseTimerEvent(EventData* ev)
{
	if (this->is_subject_attached() == true)
	{
		for (int i = 0; i < (int)pushButtons_controllers.size(); i++)
		{
			pushButtons_controllers[i]->parseTimerEvent(ev);
		}

		for (int i = 0; i < (int)edittexts_controllers.size(); i++)
		{
			edittexts_controllers[i]->parseTimerEvent(ev);
		}
	}
}

void
Controller_Transaction_GUI::forwardMouseEvent(EventData* ev) {
} // nothing

void
Controller_Transaction_GUI::forwardKeyboardEvent(EventData* ev) {} // nothing

bool
Controller_Transaction_GUI::isThisMine(EventData* ev)
{
	int myPosX = model->get_pos_x();
	int myPosY = model->get_pos_y();
	int limitX = myPosX + model->get_size_x();
	int limitY = myPosY + model->get_size_y();
	int clickPosX = ev->al_ev->mouse.x;
	int clickPosY = ev->al_ev->mouse.y;


	if (clickPosX >= myPosX && clickPosX <= limitX && clickPosY >= myPosY && clickPosY <= limitY)	// checkea si el click fue en el rango de la imagen
		return true;
	else
		return false;
}

