#include "View_Button_Blockchain.h"
#include "ImagesManager.h"

#include "Model_Button_Blockchain.h"

#define IMAGE_SIZE_DEFAULT 60

View_Button_Blockchain::
View_Button_Blockchain(const char * path_image) {

	this->image_represent = resize_image(path_image, IMAGE_SIZE_DEFAULT, IMAGE_SIZE_DEFAULT);
	this->init = true;

	if (image_represent == nullptr)
	{
		this->init = false;
	}


}

View_Button_Blockchain::
~View_Button_Blockchain(void)
{
	if (init)
	{
		al_destroy_bitmap(image_represent);
		this->init = false;

	}


}


void View_Button_Blockchain::
update(void * model) {

	Model_Button_Blockchain * actual_model = (Model_Button_Blockchain *) model;

	this->image_represent = resize_bitmap(this->image_represent, actual_model->get_width(), actual_model->get_heigth());

	al_draw_bitmap(this->image_represent, actual_model->get_pos_x(), actual_model->get_pos_y(), 0);


}




