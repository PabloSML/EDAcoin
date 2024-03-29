#include "Board.h"




//listo
board::board(int width, int height, vector<ImageDescriptor> & blocks_images, vector<ImageDescriptor> & buttons, vector<MerkleNode *> merkleTrees):
	width(width), height(height), margin_x(width * MARGIN_RATE), margin_y(height * MARGIN_RATE)
{
	
	
	
	//**Por que hay botones de right left?
	/*
		(buttons[BUTTON_LEFT]).set_pos(BUTTON_SIZE_X * MARGIN_RATE, this->height - BUTTON_SIZE_Y);
		(buttons[BUTTON_RIGHT]).set_pos(this->width - BUTTON_SIZE_X , this->height - BUTTON_SIZE_Y - (BUTTON_SIZE_Y * MARGIN_RATE));


		this->buttons = buttons;
		
	
	*/
	
	
	

	this->blocks_images = blocks_images;

	this->merkleTrees = merkleTrees;

	//**No deberia sumarle 1? porque si hago 2/9 -> 0 
	//** se esta tomando 0 como una pagina y 1 como dos paginas
	//this->board_cant = (int)( (this->blocks_images).size() / MAX_IMAGES_IN_THE_BOARD);		//Solo se puede mostrar como maximo 9 imagenes en el display.

	/* listo
	
	if (!((this->blocks_images).size() % MAX_IMAGES_IN_THE_BOARD)) //si la division es exacta
	{
		(this->board_cant)--;
	}


	this->board_actual = 0;

	
	*/
	
}

//listo
/*
Actualizo las posiciones de cada imagen en el display (sin mostrarlo).
*/

void board::refresh(void)
{
	unsigned int aux_pos_x = this->margin_x;
	unsigned int aux_pos_y = this->margin_y;

	for (unsigned int i = FIRST_IMAGE_BOARD(this->board_actual); (i < LAST_IMAGE_BOARD(this->board_actual)) && (i < (this->blocks_images).size()); i++)			//Para todas las imagenes del board actual...
	{
		/*asigno posiciones en el display para cada imagen.*/
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

	//Para cada imagen de la board actual, comparo las coordenadas de me ingresaron con el lugar que ocupa cada imagen.
	for (unsigned int i = FIRST_IMAGE_BOARD(this->board_actual); (i < LAST_IMAGE_BOARD(this->board_actual)) && (image_touched == false) && (i < (this->blocks_images).size()); i++)
	{
		aux_pos_x = ((this->blocks_images)[i]).get_pos_x();
		aux_pos_y = ((this->blocks_images)[i]).get_pos_y();
		//Si las coordenadas corresponden a una imagen, se selecciona o deselecciona.
		if (((cordx_touch >= aux_pos_x) && (cordx_touch <= (aux_pos_x + this->image_size_x))) && ((cordy_touch >= aux_pos_y) && (cordy_touch <= (aux_pos_y + image_size_y)))) //si se toco una imagen
		{
			image_touched = true;
			((this->blocks_images)[i]).toggle_selection();
		}
	}

	
	if (image_touched == false)		//Si no se toco ninguna imagen...
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
				finish--; //deshabilito el �ltimo boton
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




vector<MerkleNode *> & board::get_merkle_trees(void)
{
	return (this->merkleTrees);
}

void board::set_merkle_trees(vector<MerkleNode *> & new_merkle_trees)
{
	this->merkleTrees = new_merkle_trees;
}

void board::set_blocks_images(vector<ImageDescriptor> & new_blocks_images) {
	this->blocks_images = new_blocks_images;
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


void board::update_board(vector<ImageDescriptor> & blocks_images, vector<MerkleNode *> merkleTrees)
{
	this->blocks_images = blocks_images;

	this->merkleTrees = merkleTrees;

	this->board_cant = (int)((this->blocks_images).size() / MAX_IMAGES_IN_THE_BOARD);

	if (!((this->blocks_images).size() % MAX_IMAGES_IN_THE_BOARD)) //si la division es exacta
	{
		(this->board_cant)--;
	}

}


