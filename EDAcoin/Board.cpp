#include "Board.h"




//listo
board::board(int width, int height, vector<ImageDescriptor> & blocks_images, vector<ImageDescriptor> & buttons)
{
	this->width = width;
	this->height = height;

	this->margin_x = width * MARGIN_RATE;
	this->margin_y = height * MARGIN_RATE;

	this->blocks_images = blocks_images;
	
	

	(buttons[BUTTON_LEFT]).set_pos(BUTTON_SIZE_X * MARGIN_RATE, this->height - BUTTON_SIZE_Y);
	(buttons[BUTTON_RIGHT]).set_pos(this->width - BUTTON_SIZE_X , this->height - BUTTON_SIZE_Y - (BUTTON_SIZE_Y * MARGIN_RATE));


	this->buttons = buttons;

	this->board_cant = (int)( (this->blocks_images).size() / MAX_IMAGES_IN_THE_BOARD);

	if (!((this->blocks_images).size() % MAX_IMAGES_IN_THE_BOARD)) //si la division es exacta
	{
		(this->board_cant)--;
	}							


	this->board_actual = 0;
}

//listo
board::~board()
{
}

//listo
void board::refresh(void)
{
	unsigned int aux_pos_x = this->margin_x;
	unsigned int aux_pos_y = this->margin_y;

	for (unsigned int i = FIRST_IMAGE_BOARD(this->board_actual); (i < LAST_IMAGE_BOARD(this->board_actual)) && (i < (this->blocks_images).size()); i++)
	{

		int image_size = this->image_size_x;
		int margin = this->margin_x;

		((this->blocks_images)[i]).set_pos(aux_pos_x, aux_pos_y);

		aux_pos_x += image_size + margin;
		
		if (aux_pos_x > (this->width - margin - image_size)) //reseteo pos_x cuando llega al tope de ancho del board
		{
			aux_pos_x = margin;
			aux_pos_y += this->image_size_y + this->margin_y; //avanzo en 'y'
		}
	}
}

//listo
void board::touch(unsigned int cordx_touch, unsigned int cordy_touch)
{
	bool image_touched = false;
	
	
	unsigned int aux_pos_x = 0;
	unsigned int aux_pos_y = 0;

	for (unsigned int i = FIRST_IMAGE_BOARD(this->board_actual); (i < LAST_IMAGE_BOARD(this->board_actual)) && (image_touched == false) && (i < (this->blocks_images).size()); i++)
	{
		aux_pos_x = ((this->blocks_images)[i]).get_pos_x();
		aux_pos_y = ((this->blocks_images)[i]).get_pos_y();

		if (((cordx_touch >= aux_pos_x) && (cordx_touch <= (aux_pos_x + this->image_size_x))) && ((cordy_touch >= aux_pos_y) && (cordy_touch <= (aux_pos_y + image_size_y)))) //si se toco una imagen
		{
			image_touched = true;
			((this->blocks_images)[i]).toggle_selection();
		}
	}


	if (image_touched == false)
	{
		if (this->board_cant != 0)  //habilito botones si tengo mas de un damero 
		{
			bool button_touched = false;

			int begin = 0;  
			int finish = (int) buttons.size();
			
			
			if (this->board_actual == 0) //primer damero
			{
				begin = 1; //deshabilito el primet boton
			}
			else if (this->board_actual == this->board_cant) //ultimo damero
			{
				finish--; //deshabilito el último boton
			}
			for (int i = begin; (i < finish) && (button_touched == false); i++)
			{
				aux_pos_x = buttons[i].get_pos_x();
				aux_pos_y = buttons[i].get_pos_y();
				
				if (((cordx_touch >= aux_pos_x) && (cordx_touch <= (aux_pos_x + this->image_size_x))) && ((cordy_touch >= aux_pos_y) && (cordy_touch <= (aux_pos_y + this->image_size_y)))) //si se toco una imagen
				{
					button_touched = true;
					change_board(i);
					refresh();
				}
			}
		}

	}
}

//listo
bool board::is_some_image_select(void)
{
	bool is_select_something = false;

	for (unsigned int i = 0; (i < (this->blocks_images).size()) && (is_select_something == false) ; i++)
	{
		if (blocks_images[i].is_select() == true)
		{
			is_select_something = true;
		}
	}
	return is_select_something;
}

//listo
void board::set_image_size(unsigned int image_size_x, unsigned int image_size_y)
{
	this->image_size_x = image_size_x;
	this->image_size_y = image_size_y;
}

//listo
void board::set_button_size(unsigned int button_size_x, unsigned int button_size_y)
{
	this->button_size_x = button_size_x;
	this->button_size_y = button_size_y;
}

//listo
vector <ImageDescriptor> & board::get_block_images(void)
{
	return (this->blocks_images);
}

//listo
vector <ImageDescriptor> & board::get_buttons(void)
{
	return (this->buttons);
}

//listo
int board::get_size_x(void)
{
	return (this->image_size_x);
}

//listo
int board::get_size_y(void)
{
	return (this->image_size_y);
}

//listo
int board::get_margin_x(void)
{
	return (this->margin_x);
}

//listo
int board::get_margin_y(void)
{
	return (this->margin_y);
}

//listo
int board::get_actual_board(void)
{
	return (this->board_actual);
}

//listo
int board::get_cant(void)
{
	return (this->board_cant);
}

//listo
bool board::is_images_error(void)
{
	bool error = false;

	for (unsigned int i = 0; (i < (this->blocks_images).size()) && (error == false); i++)
	{
		if ((this->blocks_images)[i].get_error())
		{
			error = true;
		}
	}

	return error;
}




//listo
void board::change_board(int button_pressed)
{
	switch (button_pressed)
	{
		case BUTTON_LEFT:
			(this->board_actual) = (this->board_actual) - 1;
			break;
		case BUTTON_RIGHT:
			(this->board_actual) = (this->board_actual) + 1;
			break;
		}
}

