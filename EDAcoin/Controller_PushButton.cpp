#include "Controller_PushButton.h"
#include "Subject.h"


using namespace std;


//Constructor:attach del model
Controller_PushButton::Controller_PushButton(Subject* creator) : Controller(creator)
{
	Subject* subj = this->get_subject_attach();
	model = (Model_PushButton *)subj;
}

Controller_PushButton::~Controller_PushButton()
{
	//**dettach?
}


void Controller_PushButton::
parseTimerEvent(EventData * ev) //refresh
{
	if (this->is_subject_attached() == true)
	{
		model->ping();
	}
}


void Controller_PushButton::
parseMouseEvent(EventData * ev)		//manage display close
{
	if (clickInMe(ev))	// se evalua despues ya que si el click fue en el display apropiado pero en otro lado no hay que pasar el ev mas adelante
	{
		model->toggleSelect();
		model->ping();
	}
}

void Controller_PushButton::
parseKeyboardEvent(EventData * ev) //nothing
{

}




bool
Controller_PushButton::clickInMe(EventData* ev)
{
	int myPosX = model->get_pos_x();
	int myPosY = model->get_pos_y();

	int limitX = myPosX + model->get_width();
	int limitY = myPosY + model->get_heigth();

	int clickPosX = ev->al_ev->mouse.x;
	int clickPosY = ev->al_ev->mouse.y;

	if (clickPosX >= myPosX && clickPosX <= limitX && clickPosY >= myPosY && clickPosY <= limitY)	// checkea si el click fue en el rango de la imagen
		return true;
	else
		return false;
}

