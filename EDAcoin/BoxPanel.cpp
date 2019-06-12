#include "BoxPanel.h"

#define INITIAL_POS 0

BoxPanel::
BoxPanel(string& first_title, unsigned int first_width, unsigned int first_heigth) :
	Widget(first_width, first_heigth, INITIAL_POS, INITIAL_POS), title(first_title), is_selected(false)	
{
	
}


BoxPanel::
~BoxPanel()
{

}

//getters
string	BoxPanel::
get_title(void) { return this->title; }






bool BoxPanel::
is_select(void) { return this->is_selected; }


void BoxPanel::
toggleSelect(void)
{
	if (is_selected)
		is_selected = false;
	else
		is_selected = true;
}




