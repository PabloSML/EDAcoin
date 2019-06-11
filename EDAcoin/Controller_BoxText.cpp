#include "Controller_BoxText.h"
#include "Subject.h"

#include "Definitions.h"

using namespace std;


//Constructor:attach del model
Controller_BoxText::Controller_BoxText(Subject* creator) : Controller(creator)
{
	Subject* subj = this->get_subject_attach();
	model = (Model_BoxText *)subj;
}

Controller_BoxText::~Controller_BoxText()
{
	//**dettach?
}


void Controller_BoxText::
parseTimerEvent(EventData * ev) //refresh
{
	if (this->is_subject_attached() == true)
	{
		model->ping();
	}
}


void Controller_BoxText::
parseMouseEvent(EventData * ev)		//manage display close
{
	if (clickInMe(ev))	// se evalua despues ya que si el click fue en el display apropiado pero en otro lado no hay que pasar el ev mas adelante
	{
		if (model->is_select() == false)
		{
			model->toggleSelect();
			model->ping();
		}
		
	}
	else
	{
		if (model->is_select() == true)
		{
			model->toggleSelect();
			model->ping();
		}
	}
}

void Controller_BoxText::
parseKeyboardEvent(EventData * ev) //nothing
{
	if (model->is_select() == true)
	{
		
		switch (ev->al_ev->keyboard.keycode) //Para cada uno de estos casos debe actualizarse el display.
		{
			case ALLEGRO_KEY_0:
			case ALLEGRO_KEY_1:
			case ALLEGRO_KEY_2:
			case ALLEGRO_KEY_3:
			case ALLEGRO_KEY_4:
			case ALLEGRO_KEY_5:
			case ALLEGRO_KEY_6:
			case ALLEGRO_KEY_7:
			case ALLEGRO_KEY_8:
			case ALLEGRO_KEY_9:


				if (model->get_actual_text().size() < (size_t) MAX_SIZE_TEXT_BOXTEXT)
				{
					int key_num_pressed = ev->al_ev->keyboard.keycode - ALLEGRO_KEY_0;

					string str_char = to_string(key_num_pressed);

					string actual_text = model->get_actual_text() + str_char;

					model->set_text(actual_text);

					model->ping();
				}

				
				break;

			case ALLEGRO_KEY_A:
			case ALLEGRO_KEY_B:
			case ALLEGRO_KEY_C:
			case ALLEGRO_KEY_D:
			case ALLEGRO_KEY_E:
			case ALLEGRO_KEY_F:
			case ALLEGRO_KEY_G:
			case ALLEGRO_KEY_H:
			case ALLEGRO_KEY_I:
			case ALLEGRO_KEY_J:
			case ALLEGRO_KEY_K:
			case ALLEGRO_KEY_L:
			case ALLEGRO_KEY_M:
			case ALLEGRO_KEY_N:
			case ALLEGRO_KEY_O:
			case ALLEGRO_KEY_P:
			case ALLEGRO_KEY_Q:
			case ALLEGRO_KEY_R:
			case ALLEGRO_KEY_S:
			case ALLEGRO_KEY_T:
			case ALLEGRO_KEY_U:
			case ALLEGRO_KEY_V:
			case ALLEGRO_KEY_W:
			case ALLEGRO_KEY_X:
			case ALLEGRO_KEY_Y:
			case ALLEGRO_KEY_Z:


				if (model->get_actual_text().length() < (size_t)MAX_SIZE_TEXT_BOXTEXT)
				{
					

					int delta_key_char_pressed = ev->al_ev->keyboard.keycode - ALLEGRO_KEY_A;

					char key_char_pressed;

					if (ev->al_ev->keyboard.modifiers & ALLEGRO_KEYMOD_CAPSLOCK)
					{
						key_char_pressed = 'A' + delta_key_char_pressed;
					}
					else
					{
						key_char_pressed = 'a' + delta_key_char_pressed;
					}



					string actual_text = model->get_actual_text() + key_char_pressed;


					model->set_text(actual_text);

					model->ping();

				
				}


				break;

			case ALLEGRO_KEY_COMMA:


				if (model->get_actual_text().size() < (size_t)MAX_SIZE_TEXT_BOXTEXT)
				{
					
					char key_char_pressed = ',';


					string actual_text = model->get_actual_text() + key_char_pressed;

					model->set_text(actual_text);

					model->ping();
				}

				break;

			case ALLEGRO_KEY_FULLSTOP:


				if (model->get_actual_text().size() < (size_t)MAX_SIZE_TEXT_BOXTEXT)
				{

					char key_char_pressed = '.';

					string actual_text = model->get_actual_text() + key_char_pressed;

					model->set_text(actual_text);

					model->ping();
				}

			


			break;

			case ALLEGRO_KEY_DELETE:
				string str_empty= string("");

				model->set_text(str_empty);

				model->ping();

			break;
		}
	}



}




bool
Controller_BoxText::clickInMe(EventData* ev)
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


