#include "Model_Transaction_GUI.h"


#include "View_BoxText.h"
#include "View_PushButton.h"

#include "Definitions.h"

Model_Transaction_GUI::
Model_Transaction_GUI(unsigned int num_boxtexts, unsigned int  num_pushbuttons,
	const char* titles_boxtexts[], const char * titles_pushbuttons[],
	unsigned int width_boxtexts, unsigned int height_boxtexts,
	unsigned int width_pushbuttons, unsigned int height_pushbuttons,
	unsigned int dx, unsigned int dy, unsigned int margin):

	margin_btw_buttons(margin),
	pos_x(dx),
	pos_y(dy),
	init_ok(true),
	transaction_waiting(false),
	cant_pushbuttons(num_pushbuttons),
	cant_boxtexts(num_boxtexts)

{
	this->boxtexts = new vector<Model_BoxText *>;
	this->pushbuttons = new vector<Model_PushButton*>;

	for (unsigned int index_boxtext = 0; (index_boxtext < cant_boxtexts)&&init_ok; index_boxtext++)
	{
		string aux_string = string(titles_boxtexts[index_boxtext]);
		Model_BoxText * auxliar_boxtext = new Model_BoxText(aux_string, width_boxtexts, height_boxtexts);
		
		if (auxliar_boxtext == nullptr)
		{
			init_ok = false;

			for (unsigned int i = 0; i < index_boxtext; i++)
			{
				delete (*boxtexts)[i];
			}

			delete boxtexts;
			delete pushbuttons;
		}
		else
		{
			auxliar_boxtext->set_pos(dx + index_boxtext * (width_boxtexts + this->margin_btw_buttons), dy);

			boxtexts->push_back(auxliar_boxtext);


		}

	

	}


	for (unsigned int index_pushbutton = 0; (index_pushbutton < cant_pushbuttons) && init_ok; index_pushbutton++)
	{
		string aux_string = string(titles_pushbuttons[index_pushbutton]);
		Model_PushButton * auxiliar_pushbutton = new Model_PushButton(aux_string, width_pushbuttons, height_pushbuttons);
		
		if (auxiliar_pushbutton == nullptr)
		{
			init_ok = false;

			for (unsigned int i = 0; i < index_pushbutton; i++)
			{
				delete (*pushbuttons)[i];
			}

			for (unsigned int j = 0; j < cant_boxtexts; j++)
			{
				delete (*boxtexts)[j];
			}

			delete boxtexts;
			delete pushbuttons;
		}
		else
		{
			auxiliar_pushbutton->set_pos(dx + index_pushbutton * (width_pushbuttons + this->margin_btw_buttons), dy + this->margin_btw_buttons + height_boxtexts);

			pushbuttons->push_back(auxiliar_pushbutton);

		}
		
		
		
		
	}




	for (unsigned int i = 0; i < cant_boxtexts; i++)	
	{
		View_BoxText* tempView = new View_BoxText(COLOR_TITLE_PANEL, COLOR_EDIT_UNSELECT_PANEL, COLOR_EDIT_SELECT_PANEL,
												  COLOR_EDIT_TEXT, FONT_NAME_EDIT_TEXT, FONT_NAME_TITLE_EDIT,
												  (*boxtexts)[i]->get_width()*PERC_WIDTH_EDIT_TEXT,
												  (*boxtexts)[i]->get_heigth()*PERC_HEIGTH_EDIT_TEXT);
													
		(*boxtexts)[i]->attach(tempView);
	}

	for (unsigned int i = 0; i < cant_pushbuttons; i++)
	{
		View_PushButton* tempView = new View_PushButton(COLOR_PUSHB_STATE1, COLOR_PUSHB_STATE2, COLOR_PUSHB_TITLE, FONT_NAME_PUSHB_TEXT);
		(*pushbuttons)[i]->attach(tempView);
	}




}


string
Model_Transaction_GUI::get_text(unsigned int which_boxtext)
{
	string aux;
	
	if (which_boxtext < cant_boxtexts)
	{
		aux = (*boxtexts)[which_boxtext]->get_actual_text();
	}

	return aux;
}



Model_Transaction_GUI::
~Model_Transaction_GUI(void)
{
	if (init_ok == true)
	{
		for (unsigned int i = 0; i < cant_pushbuttons; i++)
		{
			delete (*pushbuttons)[i];
		}

		for (unsigned int j = 0; j < cant_boxtexts; j++)
		{
			delete (*boxtexts)[j];
		}

		delete boxtexts;
		delete pushbuttons;


	}


}










unsigned int 
Model_Transaction_GUI::get_pos_x(void)
{
	return this->pos_x;
}

unsigned int
Model_Transaction_GUI::get_pos_y(void) {

	return this->pos_y;
}



unsigned int 
Model_Transaction_GUI::get_size_x(void)
{

	unsigned int size_x;

	unsigned int size_box_texts = cant_boxtexts * ((*boxtexts)[0]->get_width() + this->margin_btw_buttons);
	unsigned int size_pushbuttons = cant_pushbuttons * ((*pushbuttons)[0]->get_width() + this->margin_btw_buttons);

	if (size_box_texts > size_pushbuttons)
	{
		size_x = size_box_texts;
	}
	else
	{
		size_x = size_pushbuttons;
	}

	return size_x;
}


unsigned int 
Model_Transaction_GUI::get_size_y(void) {

	unsigned int size_y = (*pushbuttons)[0]->get_heigth() + (*boxtexts)[0]->get_heigth() + this->margin_btw_buttons;
	return size_y;
}


unsigned int 
Model_Transaction_GUI::get_cant_pushbuttons(void) { return this->cant_pushbuttons; }

unsigned int 
Model_Transaction_GUI::get_cant_boxttexts(void) { return this->cant_boxtexts; }



Model_PushButton* 
Model_Transaction_GUI::get_pushbutton(unsigned int which_pushbutton)
{
	Model_PushButton * ret = nullptr;

	if (which_pushbutton < cant_pushbuttons)
	{
		ret = (*pushbuttons)[which_pushbutton];
	}
	
	return ret;

}
Model_BoxText*	  
Model_Transaction_GUI::get_boxtext(unsigned int which_boxttext)
{
	Model_BoxText * ret = nullptr;

	if (which_boxttext < cant_boxtexts)
	{
		ret = (*boxtexts)[which_boxttext];
	}

	return ret;
}



void 
Model_Transaction_GUI::receive_transaction(void) { this->transaction_waiting = true; }

void 
Model_Transaction_GUI::attend_transaction(void) { this->transaction_waiting = false; }

bool 
Model_Transaction_GUI::is_transaction_waiting(void) { return this->transaction_waiting; }