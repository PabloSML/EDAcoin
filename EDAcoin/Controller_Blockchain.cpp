#include "Controller_Blockchain.h"


#include "Definitions.h"


#define MAX_IMAGES_IN_THE_BOARD	9
#define FIRST_IMAGE_BOARD(button_actual) (MAX_IMAGES_IN_THE_BOARD * button_actual)
#define LAST_IMAGE_BOARD(button_actual) (MAX_IMAGES_IN_THE_BOARD * (button_actual + 1))


Controller_Blockchain::Controller_Blockchain(Model_Blockchain* owner) : Controller(owner)
{
	Subject* subj = this->get_subject_attach();
	model = (Model_Blockchain *)subj;

	vector<Model_Button_Blockchain*> buttons_model = model->get_buttons();

	Controller_Button_Blockchain * button_left_contr = new Controller_Button_Blockchain(buttons_model[BUTTON_LEFT]);
	Controller_Button_Blockchain * button_right_contr = new Controller_Button_Blockchain(buttons_model[BUTTON_RIGHT]);

	this->buttonsControllers.push_back(button_left_contr);
	this->buttonsControllers.push_back(button_right_contr);
}

Controller_Blockchain::~Controller_Blockchain(void)
{
	for (Controller_Block* C : blockControllers)
		delete C;
	blockControllers.clear();

	for (Controller_Button_Blockchain * Buttons_contr : buttonsControllers)
		delete Buttons_contr;

}

void
Controller_Blockchain::parseMouseEvent(EventData* ev)
{
	if (isThisMine(ev)) // si el evento fue en la pantalla de bchain, se ve si fue un evento de close o se clickeo en algun block
	{
		if (ev->al_ev->type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			model->triggerEnd();
		}
		else if (model->can_show_merkle_trees())  // si este modelo no puede mostrar trees, se ignora lo siguiente
		
		{
			for (int i = 0; i < (int)blockControllers.size(); i++)
			{
				MerkleNode* tree = model->getMerkleTree(i);
				blockControllers[i]->parseMouseEvent(ev, tree);
			}
		}

		unsigned int board_cant = this->model->get_cant_boards();


		if (this->buttonsControllers[BUTTON_LEFT]->clickInMe(ev) && ( model->get_actual_board() > 0 ) ) //se que no es necesario el > 0
		{
			model->set_actual_board(model->get_actual_board() - 1);
		}

		if (this->buttonsControllers[BUTTON_RIGHT]->clickInMe(ev) && (model->get_cant_boards() > model->get_actual_board())) //se que no es necesario el > 0
		{
			model->set_actual_board(model->get_actual_board() + 1);
		}


	}
	else // si el evento no fue en la pantalla de bchain, se sabe que es de merkleTree y pasa directo
	{
		for (Controller_Block* C : blockControllers)
			C->forwardMouseEvent(ev);
	}
}

void
Controller_Blockchain::parseKeyboardEvent(EventData* ev) // nothing
{
	if (isThisMine(ev))
	{
		switch (ev->al_ev->keyboard.keycode)
		{
		case ALLEGRO_KEY_RIGHT:
			if (model->get_cant_boards() > model->get_actual_board())
			{
				model->set_actual_board(model->get_actual_board()+1);
			}
			break;
		case ALLEGRO_KEY_LEFT:
			if (model->get_actual_board() > 0)
			{
				model->set_actual_board(model->get_actual_board() - 1);
			}
			break;
		}
		//**update blocks en la pagina.
	}

}

void
Controller_Blockchain::parseTimerEvent(EventData* ev)
{
	if (this->is_subject_attached() == true)
	{
		unsigned int blockCount = model->getBlockCount();	// cuantos blocks hay?
		unsigned int pending = model->recountBlocks();	// cuantos nuevos hay ahora? (se refresca la blockChain del modelo)
		for (unsigned int i = blockCount; i < blockCount + pending; i++)	// por cada nuevo se le asigna un controller y se pushea a la lista
		{
			Controller_Block* tempController = new Controller_Block(model->getBlockbyIndex(i));
			blockControllers.push_back(tempController);
		}

		this->refresh_positions_blocks_on_board();

		for (Controller_Block* C : blockControllers)
			C->parseTimerEvent(ev);
	}
}

void
Controller_Blockchain::forwardMouseEvent(EventData* ev) {
} // nothing

void
Controller_Blockchain::forwardKeyboardEvent(EventData* ev) {} // nothing

bool
Controller_Blockchain::isThisMine(EventData* ev)
{
	ALLEGRO_DISPLAY* evDisplay = ev->al_ev->touch.display;

	ALLEGRO_DISPLAY* myDisplay = model->getDisplay();

	if (evDisplay == myDisplay)
		return true;
	else
		return false;
}

bool Controller_Blockchain::shouldModelDie(void)
{
	return model->shouldEnd();
}



void Controller_Blockchain::refresh_positions_blocks_on_board(void)
{

	unsigned int board_actual = this->model->get_actual_board();
	unsigned int block_count = this->model->getBlockCount();

	unsigned int aux_pos_x = MARGIN_X_DISPLAY;
	unsigned int aux_pos_y = MARGIN_Y_DISPLAY;

	for (unsigned int i = FIRST_IMAGE_BOARD(board_actual); (i < LAST_IMAGE_BOARD(board_actual)) && (i < block_count); i++)
	{

		int image_size_x = this->model->getBlockbyIndex(i)->get_size_x();
		int image_size_y = this->model->getBlockbyIndex(i)->get_size_y();

		unsigned int width = al_get_display_width(this->model->getDisplay());

		int margin_x = MARGIN_X_DISPLAY;

		this->model->getBlockbyIndex(i)->set_pos_x(aux_pos_x);
		this->model->getBlockbyIndex(i)->set_pos_y(aux_pos_y);

		aux_pos_x += image_size_x + margin_x;



		if (aux_pos_x > (width - margin_x - image_size_x)) //reseteo pos_x cuando llega al tope de ancho del board
		{
			aux_pos_x = margin_x;
			aux_pos_y += image_size_y + MARGIN_Y_DISPLAY; //avanzo en 'y'
		}
	}
}