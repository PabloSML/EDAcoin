#include "View_Block.h"
#include "Definitions.h"
#include "Model_Block.h"

#include "ImagesManager.h"
#include "allegro5/allegro_color.h"


View_Block::
View_Block(void)
{
	
	this->bitmap = al_load_bitmap(IMAGE_BLOCK_PATH);

	if (this->bitmap == nullptr) {
		this->init_ok = false;
	}
	else
	{
		this->font = al_load_font(FONT_PATH_BLOCK_NAME, FONT_SIZE_BLOCK_NAME, 0);

		if (this->font == nullptr)
		{
			al_destroy_bitmap(this->bitmap);
			this->init_ok = false;
		}
		else
		{
			this->init_ok = true;
		}
		
	}

}


View_Block::
~View_Block(void)
{
	if (this->init_ok == true)
	{
		al_destroy_bitmap(this->bitmap);
		al_destroy_font(this->font);
		this->init_ok = false;
	}
}

void View_Block::
update(void * model) {

	 Model_Block * model_observed = (Model_Block *) model;

	float size_x = (float) model_observed->get_size_x();
	float size_y = (float) model_observed->get_size_y();

	float pos_x = (float) model_observed->get_pos_x() + size_x/2;
	float pos_y = (float) model_observed->get_pos_y() + size_y + MARGIN_BLOCK_BTW_NAME_AND_IMAGE;

	const char * name_block = ((model_observed)->getBlockID()).c_str();


	this->bitmap = resize_bitmap(this->bitmap, size_x, size_y);

	al_draw_bitmap(this->bitmap, (float)model_observed->get_pos_x(), (float)model_observed->get_pos_y(), 0);

	string aux = "Block ID: ";
	string id = string(name_block);

	id = aux + id;

	al_draw_text(this->font, al_color_name(FONT_COLOR_BLOCK_NAME), pos_x, pos_y, ALLEGRO_ALIGN_CENTER, id.c_str());

}


bool View_Block::
init_was_ok(void)
{
	return this->init_ok;
}