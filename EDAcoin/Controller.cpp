#include "Controller.h"

Controller::
~Controller(){}

void Controller::
attach_subject(Subject * subject_to_attach)
{
	subject_attach = subject_to_attach;

}


void Controller::
dettach_subject(void)
{ 

	subject_attach = nullptr;

}

Subject* Controller::
get_subject_attach(void)
{
	return this->subject_attach;
}


bool Controller::
is_subject_attached(void)
{
	bool is_attached = true;
	
	if (this->subject_attach == nullptr)
	{
		is_attached = false;
	}

	return is_attached;
}