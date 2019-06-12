#include "View_Blockchain.h"

#include "Model_Blockchain.h"
#include "View_Block.h"
#include "Model_Block.h"
#include <vector>
#include "allegro5/allegro_color.h"

#define MAX_BLOCKS_PER_DISPLAY 9

#define BUTTON_LEFT		0
#define BUTTON_RIGHT	1

#define FIRST_IMAGE_BOARD(button_actual) (MAX_BLOCKS_PER_DISPLAY * button_actual)
#define LAST_IMAGE_BOARD(button_actual) (MAX_BLOCKS_PER_DISPLAY * (button_actual + 1))

View_Blockchain::
View_Blockchain(unsigned int width_display, unsigned int heigth_display):
	graph_resources(),
	margin_x(MARGIN_RATE*width_display), margin_y(MARGIN_RATE*heigth_display)
{
	

	//**
	this->width = width_display;
	this->height = heigth_display;
	//**

}

View_Blockchain::
~View_Blockchain(void)
{
	
}

void View_Blockchain::
update(void* model) {

	Model_Blockchain * model_observed = (Model_Blockchain *) model;

	al_set_target_backbuffer(model_observed->getDisplay());

	al_clear_to_color(al_color_name(COLOR_BACKGROUND_BLOCKCHAIN));

	unsigned int actual_board = model_observed->get_actual_board();
	unsigned int cant_boards = model_observed->get_cant_boards();


	if (model_observed->getBlockCount() != 0) //si tengo por lo menos una imagen en el tablero
	{
	
		if (actual_board > 0) //DIBUJO AL BOTON DE IZQUIERDA?
		{
			model_observed->get_buttons()[BUTTON_LEFT]->ping();
		}
		
		
		if (actual_board < cant_boards)  //DIBUJO AL BOTON DE DERECHA?
		{
			model_observed->get_buttons()[BUTTON_RIGHT]->ping();
		}

	}
	

	for (unsigned int index = 0; (index + actual_board*MAX_BLOCKS_PER_DISPLAY  < model_observed->getBlockCount())&&(index < MAX_BLOCKS_PER_DISPLAY); index++)
	{
		model_observed->updateBlocksbyIndex(index + actual_board * MAX_BLOCKS_PER_DISPLAY);
	}

	al_flip_display();
}