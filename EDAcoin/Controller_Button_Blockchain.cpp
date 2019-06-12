#include "Controller_Button_Blockchain.h"
#include "Subject.h"


using namespace std;


//Constructor:attach del model
Controller_Button_Blockchain::Controller_Button_Blockchain(Subject* creator) : Controller(creator)
{
	Subject* subj = this->get_subject_attach();
	model = (Model_Button_Blockchain *)subj;
}

Controller_Button_Blockchain::~Controller_Button_Blockchain()
{
	//**dettach?
}


void Controller_Button_Blockchain::
parseTimerEvent(EventData * ev)
{

}


void Controller_Button_Blockchain::
parseMouseEvent(EventData * ev)		
{

}

void Controller_Button_Blockchain::
parseKeyboardEvent(EventData * ev) 
{

}




bool
Controller_Button_Blockchain::clickInMe(EventData* ev)
{
	int myPosX = model->get_pos_x();
	int myPosY = model->get_pos_y();

	int limitX = myPosX + model->get_width();
	int limitY = myPosY + model->get_heigth();

	int clickPosX = ev->al_ev->mouse.x;
	int clickPosY = ev->al_ev->mouse.y;

	if ((clickPosX >= myPosX) && (clickPosX <= limitX) && (clickPosY >= myPosY) && (clickPosY <= limitY))	// checkea si el click fue en el rango de la imagen
		return true;
	else
		return false;
}



