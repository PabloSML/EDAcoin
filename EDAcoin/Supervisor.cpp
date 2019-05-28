#include "Supervisor.h"
#include <iostream>

#define INDEX_PRINCIPAL_DISPLAY 0

//auxiliar function
void refresh_display(viewer& viewer_, board& board_);
bool draw_merkle_tree(MerkleNode * merkleRoot, ALLEGRO_DISPLAY * * new_display);

void draw_nodes(MerkleNode * merkleRoot, unsigned int last_pos_x, unsigned int last_pos_y,
	unsigned int depth, unsigned int level, unsigned int width, unsigned int height, ALLEGRO_FONT * font);

unsigned int get_depth_tree(MerkleNode * merkle_root);

//listo
supervisor::supervisor(viewer& viewer)
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

		(this->displays).push_back(viewer.get_display());
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
	std::vector<MerkleNode *> & merkleTrees = board.get_merkle_trees();

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
					
					ALLEGRO_DISPLAY * new_display;

					draw_merkle_tree(merkleTrees[i], &new_display);

					(this->displays).push_back(new_display);

					(vector_images)[i].toggle_selection();
					
					al_flip_display();
					
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
						
				ALLEGRO_DISPLAY * new_display;

				draw_merkle_tree(merkleTrees[i], &new_display);

				(this->displays).push_back(new_display);

				(vector_images)[i].toggle_selection();

				al_flip_display();
				
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

bool draw_merkle_tree(MerkleNode * merkleRoot, ALLEGRO_DISPLAY * * new_display)
{
	bool all_ok = true;

	*new_display = al_create_display(WIDTH_DEFAULT*(UNIT), HEIGHT_DEFAULT*(UNIT));

	if (*new_display == nullptr)
	{
		all_ok = false;
		return all_ok;
	}

	unsigned int depth_tree = get_depth_tree(merkleRoot);
	unsigned int level = 0;
	unsigned int root_pos_y = HEIGHT_DEFAULT / depth_tree;
	unsigned int root_pos_x = WIDTH_DEFAULT / 2;


	ALLEGRO_FONT* font_nodes = al_load_ttf_font(NODE_FONT_PATH, NODE_FONT_SIZE, 0);
	
	if (font_nodes == nullptr)
	{
		all_ok = false;
		return all_ok;
	}
		
	draw_nodes(merkleRoot, root_pos_x, root_pos_y, depth_tree, level + 1, WIDTH_DEFAULT, HEIGHT_DEFAULT, font_nodes);

	return all_ok; //true

}


void draw_nodes(MerkleNode * merkleRoot, unsigned int last_pos_x, unsigned int last_pos_y,
				unsigned int depth, unsigned int level, unsigned int width, unsigned int height, ALLEGRO_FONT * font)
{
	al_draw_filled_circle(last_pos_x, last_pos_x, NODE_RADIUS, NODE_COLOR);
	
	if (!(merkleRoot->getLeft() == nullptr))
	{
		unsigned int child_pos_x = last_pos_x - height / pow(2, level + 1);
		unsigned int child_pos_y = last_pos_y + (level + 1)*(height / depth);

		al_draw_line((float)(last_pos_x), (float)(last_pos_y), (float)child_pos_x, (float)child_pos_y, LINE_COLOR, LINE_THICKNESS);

		draw_nodes(merkleRoot->getLeft(), child_pos_x , child_pos_y, depth, level + 1, width, height, font);
	}

	if (!(merkleRoot->getRight() == nullptr))
	{
		unsigned int child_pos_x = last_pos_x + height / pow(2, level + 1);
		unsigned int child_pos_y = last_pos_y + (level + 1)*(height / depth);

		al_draw_line((float)(last_pos_x), (float)(last_pos_y), (float)child_pos_x, (float)child_pos_y, LINE_COLOR, LINE_THICKNESS);

		draw_nodes(merkleRoot->getRight(), child_pos_x, child_pos_y, depth, level + 1, width, height, font);
	}
	

	al_draw_text(font, MESSAGE_NODE_COLOR, (float)(last_pos_x), (float)(last_pos_y),
				ALLEGRO_ALIGN_CENTER, (merkleRoot->getNodeID()).c_str());

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
