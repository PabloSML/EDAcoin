#include "General_Controller.h"
#include "Definitions.h"
#include <allegro5\allegro.h>
#include "Supervisor.h"

#define ERROR -1

General_Controller::General_Controller(void): general_viewer()
{
	this->all_ok = true;


	vector<MerkleNode *> merkle_trees;
	vector<ImageDescriptor> block_images;

	ImageDescriptor button_left(PATH_BUTTON_LEFT); //init de los botones
	ImageDescriptor button_right(PATH_BUTTON_RIGHT);

	buttons.push_back(button_left);
	buttons.push_back(button_right);

	board general_board(WIDTH_DEFAULT, HEIGHT_DEFAULT, block_images, buttons, merkle_trees);
	

	general_board.set_blocks_images(block_images);
		
	if (general_board.is_images_error())
	{
		cout << "Image initialization Failed" << endl;
		all_ok = ERROR;
	}



	
	
	

		

	

}

General_Controller::~General_Controller(void)
{

}

void General_Controller::update(vector<Block> * blockChain, vector<MerkleNode *> merkle_trees) {

	if (!(general_supervisor->is_finish()))
	{
		vector<ImageDescriptor> block_images;

			for (int i = 0; i < ((int)blockChain->size()); i++)
			{
				ImageDescriptor image = (*blockChain)[i];
					block_images.push_back(image);

			}

		(this->general_board).update_board(block_images, merkle_trees);

		(this->general_board).set_image_size(IMAGE_SIZE_X, IMAGE_SIZE_Y);

		(this->general_board).refresh();

		(this->general_viewer).update_display((this->general_board));
		al_set_target_backbuffer((this->general_viewer).get_display());
		al_flip_display();

		if (!((this->general_viewer).is_init()))
		{
			cout << "Viewer Failed to initialize" << endl;
			this->all_ok = ERROR;
		}

	}

	
	

}

void General_Controller::dispatcher(void)
{
	general_supervisor->dispatcher((this->general_viewer), (this->general_board));
}

bool General_Controller::is_finish(void)
{
	return general_supervisor->is_finish();
}

viewer& General_Controller::get_viewer(void)
{
	return this->general_viewer;
}

void General_Controller::set_supervisor(supervisor & superv)
{
	(this->general_supervisor) = &superv;
	(this->general_supervisor)->set_start();
}