#include "BoxPanel.h"

#define INITIAL_POS 0

BoxPanel::
BoxPanel(string& first_title, unsigned int first_width, unsigned int first_heigth) :
	title(first_title), width(first_width), heigth(first_heigth), is_selected(false),
	pos_x(INITIAL_POS), pos_y(INITIAL_POS)
{
	
}


BoxPanel::
~BoxPanel()
{

}

//getters
string	BoxPanel::
get_title(void) { return this->title; }





unsigned int BoxPanel::
get_pos_x(void) { return this->pos_x; }


unsigned int BoxPanel::
get_pos_y(void) { return this->pos_y; }


unsigned int BoxPanel::
get_width(void) { return this->width; }


unsigned int BoxPanel::
get_heigth(void) { return this->heigth; }


bool BoxPanel::
is_select(void) { return this->is_selected; }




void BoxPanel::
set_pos_x(unsigned int new_pos_x) { this->pos_x = new_pos_x; }


void BoxPanel::
set_pos_y(unsigned int new_pos_y) { this->pos_y = new_pos_y; }


void BoxPanel::
set_width(unsigned int new_width) { this->width = new_width; }


void BoxPanel::
set_heigth(unsigned int new_heigth) { this->heigth = new_heigth; }
