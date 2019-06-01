#include "Supervisor.h"
#include <iostream>

#define INDEX_PRINCIPAL_DISPLAY 0


//auxiliar function
void refresh_display(viewer& viewer_, board& board_, ALLEGRO_DISPLAY * display);
bool draw_merkle_tree(MerkleNode * merkleRoot, ALLEGRO_DISPLAY * * new_display);

void draw_nodes(MerkleNode * merkleRoot, unsigned int last_pos_x, unsigned int last_pos_y,
	unsigned int depth, unsigned int level, unsigned int width, unsigned int height, ALLEGRO_FONT * font);

unsigned int get_depth_tree(MerkleNode * merkle_root);

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

bool draw_merkle_tree(MerkleNode * merkleRoot, ALLEGRO_DISPLAY * * new_display)
{
	bool all_ok = true;
	
	unsigned int actual_width = WIDTH_DEFAULT * (UNIT)+ 2 * MARGIN_X_DISPLAY*(UNIT);
	unsigned int actual_heigth = HEIGHT_DEFAULT * (UNIT) + 2 * MARGIN_Y_DISPLAY*(UNIT);


	*new_display = al_create_display(actual_width , actual_heigth );
	al_clear_to_color(al_map_rgb(255, 255, 255));

	if (*new_display == nullptr)
	{
		all_ok = false;
		return all_ok;
	}

	unsigned int depth_tree = get_depth_tree(merkleRoot);
	unsigned int level = 1;
	unsigned int root_pos_y = 0;
	unsigned int root_pos_x = WIDTH_DEFAULT / 2;


	ALLEGRO_FONT* font_nodes = al_load_ttf_font(NODE_FONT_PATH, NODE_FONT_SIZE*(1+(SCALE_LEVEL_SIZE_TEXT_NODE -1)/depth_tree), 0);
	
	if (font_nodes == nullptr)
	{
		all_ok = false;
		return all_ok;
	}
		
	draw_nodes(merkleRoot, root_pos_x, root_pos_y, depth_tree, level, WIDTH_DEFAULT, HEIGHT_DEFAULT, font_nodes);

	return all_ok; //true

}


void draw_nodes(MerkleNode * merkleRoot, unsigned int last_pos_x, unsigned int last_pos_y,
				unsigned int depth, unsigned int level, unsigned int width, unsigned int height, ALLEGRO_FONT * font)
{
	
	if (!(merkleRoot->getLeft() == nullptr))
	{
		unsigned int child_pos_x = last_pos_x - width / pow(2, level + 1);
		unsigned int child_pos_y =  (level)*(height / depth);

		al_draw_line((float)(last_pos_x + MARGIN_X_DISPLAY * (UNIT)), (float)(last_pos_y + MARGIN_Y_DISPLAY * (UNIT)),
			(float)(child_pos_x + MARGIN_X_DISPLAY * (UNIT)), (float)(child_pos_y + MARGIN_Y_DISPLAY * (UNIT)),
			LINE_COLOR, LINE_THICKNESS);


		draw_nodes(merkleRoot->getLeft(), child_pos_x , child_pos_y, depth, level + 1, width, height, font);
	}

	if (!(merkleRoot->getRight() == nullptr))
	{
		unsigned int child_pos_x = last_pos_x + width / pow(2, level + 1);
		unsigned int child_pos_y = (level)*(height / depth);

		al_draw_line((float)(last_pos_x + MARGIN_X_DISPLAY * (UNIT)), (float)(last_pos_y + MARGIN_Y_DISPLAY * (UNIT)),
					(float)(child_pos_x + MARGIN_X_DISPLAY * (UNIT)), (float)(child_pos_y + MARGIN_Y_DISPLAY * (UNIT)),
					LINE_COLOR, LINE_THICKNESS);

		draw_nodes(merkleRoot->getRight(), child_pos_x, child_pos_y, depth, level + 1, width, height, font);
	}
	
	al_draw_filled_circle(last_pos_x + MARGIN_X_DISPLAY * (UNIT), last_pos_y + MARGIN_Y_DISPLAY * (UNIT),
							NODE_RADIUS*(1+SCALE_LEVEL_SIZE_NODE/level), NODE_COLOR);

	if (merkleRoot->isLeaf())
	{
		al_draw_text(font, MESSAGE_NODE_COLOR, (float)(last_pos_x + MARGIN_X_DISPLAY * (UNIT)), (float)(last_pos_y + MARGIN_Y_DISPLAY * (UNIT) -(1+1/depth) *DX_TEXT),
			ALLEGRO_ALIGN_CENTER, (merkleRoot->getNodeID()).c_str());

	}

	
}

unsigned int get_depth_tree(MerkleNode * merkle_root)
{
	if (merkle_root->getLeft() == nullptr)
	{
		return 0;
	}
	else
	{
		return (1 + get_depth_tree(merkle_root->getLeft()));
	}
}
