#include "View_Blockchain.h"

#include "Model_Blockchain.h"
#include "View_Block.h"
#include "Model_Block.h"
#include <vector>

#define MAX_BLOCKS_PER_DISPLAY 9

#define BUTTON_LEFT		0
#define BUTTON_RIGHT	1

#define FIRST_IMAGE_BOARD(button_actual) (MAX_BLOCKS_PER_DISPLAY * button_actual)
#define LAST_IMAGE_BOARD(button_actual) (MAX_BLOCKS_PER_DISPLAY * (button_actual + 1))

View_Blockchain::
View_Blockchain(unsigned int width_display, unsigned int heigth_display):
	graph_resources(width_display,heigth_display),
	margin_x(MARGIN_RATE*width_display), margin_y(MARGIN_RATE*heigth_display)
{
	(this->buttons)[BUTTON_LEFT] = ImageDescriptor(PATH_BUTTON_LEFT);
	(this->buttons)[BUTTON_RIGHT] = ImageDescriptor(PATH_BUTTON_RIGHT);

	(buttons[BUTTON_LEFT]).set_pos(BUTTON_SIZE_X * MARGIN_RATE, heigth_display - BUTTON_SIZE_Y);
	(buttons[BUTTON_RIGHT]).set_pos(width_display - BUTTON_SIZE_X, heigth_display - BUTTON_SIZE_Y - (BUTTON_SIZE_Y * MARGIN_RATE));

}

View_Blockchain::
~View_Blockchain(void)
{

}

void View_Blockchain::
update(void* model) {

	Model_Blockchain * model_observed = (Model_Blockchain *) model;

	vector<Model_Block> * aux_blockchain = model_observed->get_blockchain();

	View_Block aux_viewer_block = View_Block();
	

	
	/*

	va en controller lo siguiente
	
	for (unsigned int i = FIRST_IMAGE_BOARD(actual_board); (i < LAST_IMAGE_BOARD(actual_board)) && (i < cant_blocks); i++)			//Para todas las imagenes del board actual...
	{
	
	unsigned int aux_pos_x = this->margin_x;
	unsigned int aux_pos_y = this->margin_y;

	unsigned int actual_board = model_observed->get_actual_board();
	unsigned int cant_blocks = (unsigned int) (model_observed->get_blockchain()).size();


	int image_size_x = ((aux_blockchain)[i]).size_x;
	int margin = this->margin_x;

	((aux_blockchain)[i]).set_pos(aux_pos_x, aux_pos_y);

	aux_pos_x += image_size_x + margin;

	if (aux_pos_x > ((this->graph_resources).GetDisplayW() - margin - image_size_x)) //reseteo pos_x cuando llega al tope de ancho del board
	{
		aux_pos_x = margin;
		aux_pos_y += ((aux_blockchain)[i]).size_y + this->margin_y; //avanzo en 'y' !! SUPONGO QUE TODOS LOS BLOQUES SON IGUALES EN SIZE_Y
	}
}

	*/

	unsigned int actual_board = model_observed->get_actual_board();
	unsigned int cant_boards = model_observed->get_cant_boards();

	unsigned int cant_blocks = (unsigned int)(model_observed->get_blockchain())->size();

	if (cant_blocks != 0) //si tengo por lo menos una imagen en el tablero
	{
		bool button_touched = false;
		int first_button = 0;  //en principio, deseo tener en cuenta todo el vector de botones.
		int last_button = (int) (this->buttons).size();



		if (actual_board == 0) //primer damero
		{
			first_button = 1; //salteo el primer boton.
		}
		else if (actual_board == cant_boards) //ultimo damero
		{
			last_button--; //descarto el último boton.
		}


		for (int i = first_button; (i < last_button) && (!button_touched); i++)
		{
			ImageDescriptor button = (this->buttons)[i];

			ALLEGRO_BITMAP * image_button = button.get_bitmap();

			ALLEGRO_BITMAP * image_button_resize = resize_bitmap(image_button, BUTTON_SIZE_X, BUTTON_SIZE_Y);

			int button_pos_x = button.get_pos_x();
			int button_pos_y = button.get_pos_y();

			graph_resources.drawImage(image_button_resize, button_pos_x, button_pos_y);

		}
	}
	

	for (unsigned int index = 0; (index + actual_board*MAX_BLOCKS_PER_DISPLAY  < (*aux_blockchain).size())&&(index < MAX_BLOCKS_PER_DISPLAY); index++)
	{

		Model_Block block = (*aux_blockchain)[index + actual_board * MAX_BLOCKS_PER_DISPLAY];
		Model_Block * p_block = &block;
		aux_viewer_block.update((void*)p_block);

	}

}