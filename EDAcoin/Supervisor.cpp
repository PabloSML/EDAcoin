#include "Supervisor.h"
#include <iostream>

#define INDEX_PRINCIPAL_DISPLAY 0


//auxiliar function
void refresh_display(viewer& viewer_, board& board_, ALLEGRO_DISPLAY * display);

//listo
supervisor::supervisor(viewer& viewer)
{
	this->init = true;
	this->finish = false;
	this->start = false;

	
	this->timer_fps = al_create_timer(1.0 / FPS);

	if ((this->timer_fps == nullptr))
	{
		
		this->init = false;
		this->finish = false;

	}
	else
	{
		this->ev_queue = al_create_event_queue();

		if ((ev_queue == nullptr) && (this->init))
		{
			if (this->init)
			{
				al_destroy_timer(this->timer_fps);
			}

			this->init = false;
			this->finish = false;

		}
		else if (this->init)
		{
			al_register_event_source(ev_queue, al_get_timer_event_source(this->timer_fps));
			al_register_event_source(ev_queue, al_get_display_event_source(viewer.get_display()));
			al_register_event_source(ev_queue, al_get_mouse_event_source());
			al_register_event_source(ev_queue, al_get_keyboard_event_source());

			this->actual_display = viewer.get_display();
			(this->displays).push_back(viewer.get_display());
		}

	}
}




	

//listo
supervisor::~supervisor()
{
	if (this->init)
	{
		al_destroy_timer(this->timer_fps);
		al_destroy_event_queue(this->ev_queue);

		this->start = false;
		this->init = false;

	}
	
}

supervisor::supervisor(void)
{

}



void supervisor::
set_start(void) {
	this->start = true;
	al_start_timer(this->timer_fps);
}

//listo
void supervisor::dispatcher(viewer& viewer, board& board)
{
	if (this->start)
	{
		ALLEGRO_EVENT ev;
		al_get_next_event(ev_queue, &ev);
		unsigned int key_pressed;
		std::vector<ImageDescriptor> & vector_images = board.get_block_images();
		std::vector<MerkleNode *> & merkleTrees = board.get_merkle_trees();

		switch (ev.type)
		{
		case ALLEGRO_EVENT_DISPLAY_CLOSE:

		
			if (this->actual_display == displays[INDEX_PRINCIPAL_DISPLAY])
			{
				this->finish = true;

				for (int i = 0; i < (int) this->displays.size(); i++)
				{				
					if (((this->displays)[i] != nullptr) && (i != 0) )
					{
						al_destroy_display((this->displays)[i]);
						(this->displays)[i] = nullptr;
					}

				}

			}
			else
			{

				for (int i = 0; i < (int)this->displays.size(); i++)
				{
					if (this->actual_display == (this->displays)[i])
					{
						al_destroy_display((this->displays)[i]);
						(this->displays)[i] = nullptr;
					}
				}

				this->actual_display = nullptr;
				
			}
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

				(vector_images)[key_pressed].toggle_selection();


				break;
			}
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			
			this->actual_display = ev.touch.display;

			if (this->actual_display == displays[INDEX_PRINCIPAL_DISPLAY])
			{
				board.touch((int)ev.mouse.x, (int)ev.mouse.y);
				refresh_display(viewer, board, this->actual_display);

			}
			
			break;

		case ALLEGRO_EVENT_TIMER:


			for (unsigned int i = 0; (i < vector_images.size()); i++)
			{
				if ((vector_images[i]).is_select())
				{

					ALLEGRO_DISPLAY * new_display;
					
					draw_merkle_tree(merkleTrees[i], &new_display);
					
					if (new_display != nullptr)
					{
						(this->displays).push_back(new_display);
						this->actual_display = new_display;
						al_register_event_source(ev_queue, al_get_display_event_source(this->actual_display));
						
					}

					(vector_images)[i].toggle_selection();

				}
			}

			if (this->actual_display != nullptr)
			{
				al_set_target_backbuffer(this->actual_display);
				al_flip_display();
			}
			

			break;

		}
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


void refresh_display(viewer& viewer_, board& board_, ALLEGRO_DISPLAY * display)
{
	al_set_target_backbuffer(display);
	viewer_.update_display(board_);
	al_flip_display();
}

