#include "Model_BoxText.h"

Model_BoxText::
Model_BoxText(string& first_title, unsigned int first_width, unsigned int first_heigth) :
	BoxPanel(first_title, first_width, first_heigth)
{

}

Model_BoxText::
~Model_BoxText(void)
{

}

//getters
string	Model_BoxText::
get_actual_text(void) { return this->buffer_edit_text; }


//setters
void Model_BoxText::
set_text(string& new_text) { this->buffer_edit_text = new_text; }
