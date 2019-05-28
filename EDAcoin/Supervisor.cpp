#include "Supervisor.h"

#include <iostream>

//auxiliar function
void refresh_display(viewer& viewer_, board& board_);


//listo
supervisor::supervisor(viewer& viewer, double threshold)
{
	this->init = true;
	this->finish = false;

	if (!al_install_keyboard())
	{
		this->init = false;
		this->finish = false;
	}
	if ( (!al_install_mouse()) && (this->init))
	{
		if (this->init)
		{
			al_uninstall_keyboard();
		}

		this->init = false;
		this->finish = false;
	}


	this->ev_queue = al_create_event_queue();
	
	if (ev_queue == nullptr)
	{
		al_uninstall_mouse();
		al_uninstall_keyboard();

		this->init = false;
		this->finish = false;

	}
	else if (this->init)
	{
		al_register_event_source(ev_queue, al_get_display_event_source(viewer.get_display()));
		al_register_event_source(ev_queue, al_get_mouse_event_source());
		al_register_event_source(ev_queue, al_get_keyboard_event_source());

		this->threshold = threshold;

	}
	
}

//listo
supervisor::~supervisor()
{
	if (this->init)
	{
		al_uninstall_mouse();
		al_uninstall_keyboard();
		al_destroy_event_queue(this->ev_queue);

		this->init = false;

	}
	
}

//listo
void supervisor::dispatcher(viewer& viewer, board& board)
{
	ALLEGRO_EVENT ev;
	al_get_next_event(ev_queue, &ev);
	unsigned int key_pressed;
	std::vector<ImageDescriptor> & vector_images = board.get_block_images();

	switch (ev.type)
	{
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		this->finish = true;
		break;

	case ALLEGRO_EVENT_KEY_DOWN:
		switch (ev.keyboard.keycode) //Para cada uno de estos casos debe actualizarse el display.
		{

		case ALLEGRO_KEY_1:
		case ALLEGRO_KEY_2:
		case ALLEGRO_KEY_3:
		case ALLEGRO_KEY_4:
		case ALLEGRO_KEY_5:
		case ALLEGRO_KEY_6:
		case ALLEGRO_KEY_7:
		case ALLEGRO_KEY_8:
		case ALLEGRO_KEY_9:

			key_pressed = ev.keyboard.keycode - ALLEGRO_KEY_1;

			vector_images = board.get_block_images();

			for (unsigned int i = 0; (i < vector_images.size()); i++)
			{
				if ((vector_images[i]).is_select())
				{
					#error "aca hay que poner la funcion que muestre ese merkle tree"

					(vector_images)[i].toggle_selection();
					found_touched = true;

				}
			}


			(vector_images)[key_pressed].toggle_selection();

			refresh_display(viewer, board);

			vector_images[key_pressed];

			(vector_images)[key_pressed].toggle_selection();

			break;
		}
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		board.touch( (int)ev.mouse.x, (int)ev.mouse.y );
		
		refresh_display(viewer, board);
		
		bool found_touched = false;

		for (unsigned int i = 0; (i < vector_images.size() )&& (!found_touched); i++)
		{
			if ((vector_images[i]).is_select())
			{
				#error "aca hay que poner la funcion que muestre ese merkle tree"

				(vector_images)[i].toggle_selection();
				found_touched = true;

			}
		}
		break;

	}
}

//listo
bool supervisor::is_init(void)
{
	return (this->init);
}

//listo
bool supervisor::is_finish(void)
{
	return (this->finish);
}


void refresh_display(viewer& viewer_, board& board_)
{
	al_set_target_backbuffer(viewer_.get_display());
	viewer_.update_display(board_);
	al_flip_display();
}