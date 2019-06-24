#include "Simulation.h"
#include "Definitions.h"

Simulation::Simulation(ALLEGRO_EVENT_QUEUE* queue)
{
	display = al_create_display(WIDTH_DEFAULT, HEIGHT_DEFAULT + HEIGHT_EXTRA);
	if (!display)
	{
		cout << "Error creating sim display!" << endl;
		init_ok = false;
	}
	else
	{
		al_register_event_source(queue, al_get_display_event_source(display));
		init_ok = true;
	}

	const char * titles_pushb [] = { TRANS_INTERF_PUSHB_TITLE1 };
	const char * titles_editb [] = { TRANS_INTERF_EDITB_TITLE1 , TRANS_INTERF_EDITB_TITLE2 , TRANS_INTERF_EDITB_TITLE3 };

	unsigned int cant_pushbuttons = TRANS_INTERF_CANT_PUSHB;
	unsigned int cant_edittexts   = TRANS_INTERF_CANT_EDITB;

	unsigned int size_x_pushbutton = TRANS_INTERF_PUSHB_WIDTH;
	unsigned int size_x_edittext   = TRANS_INTERF_EDITB_WIDTH;

	unsigned int size_y_pushbutton = TRANS_INTERF_PUSHB_HEIGTH;
	unsigned int size_y_edittext   = TRANS_INTERF_EDITB_HEIGTH;

	unsigned int max_cant_buttons = 0;
	unsigned int max_size_x		  = 0;

	unsigned int margin = TRANS_INTERF_MARGIN_BTW_B;

	if (cant_pushbuttons*size_x_pushbutton < cant_edittexts*size_x_edittext)
	{
		max_cant_buttons = cant_edittexts;
		max_size_x		 = size_x_edittext;
	}
	else
	{
		max_cant_buttons = cant_pushbuttons;
		max_size_x		 = size_x_pushbutton;
	}

	
	unsigned int size_x_display = (unsigned int) al_get_display_width((this->getDisplay()));

	unsigned int size_x_interface = max_cant_buttons * max_size_x + (max_cant_buttons - 1)*margin;
	unsigned int pos_x			  = (size_x_display - size_x_interface) / 2;
	unsigned int pos_y			  = TRANS_INTERF_POS_Y;

	this->transaction_interface = new Model_Transaction_GUI(cant_edittexts, cant_pushbuttons,
															titles_editb, titles_pushb,
															size_x_edittext, size_y_edittext,
															size_x_pushbutton, size_y_pushbutton,
															pos_x, pos_y,
															margin);

}

Simulation::~Simulation(void)
{
	if (init_ok == true)
	{
		al_destroy_display(display);
		init_ok = false;
		delete transaction_interface;
		for (Node* N : nodes)
			delete N;
	}
}

void
Simulation::addNode(Node* node)
{
	nodes.push_back(node);
	notifyObservers();
}

bool
Simulation::removeNode(Node* node)
{
	bool success = false;
	size_t currentSize = nodes.size();

	nodes.remove(node);

	if (currentSize - 1 == nodes.size())
	{
		notifyObservers();
		success = true;
	}

	return success;
}

/*
void
Simulation::addTextBox(Model_BoxText* box)
{
	textBoxes.push_back(box);
	notifyObservers();
}

bool
Simulation::removeTextBox(Model_BoxText* box)
{
	bool success = false;
	size_t currentSize = textBoxes.size();

	textBoxes.remove(box);

	if (currentSize - 1 == textBoxes.size())
	{
		notifyObservers();
		success = true;
	}

	return success;
}

void
Simulation::addButton(Model_PushButton* button)
{
	buttons.push_back(button);
	notifyObservers();
}

bool
Simulation::removeButton(Model_PushButton* button)
{
	bool success = false;
	size_t currentSize = buttons.size();

	buttons.remove(button);

	if (currentSize - 1 == buttons.size())
	{
		notifyObservers();
		success = true;
	}

	return success;
}
*/

void
Simulation::updateInsiderModels(void)
{
	for (Node* N : nodes)
	{
		al_set_target_backbuffer(display);
		N->ping();
		al_set_target_backbuffer(display);
	}

	for (unsigned int i = 0; i < transaction_interface->get_cant_boxttexts(); i++)
		(transaction_interface->get_boxtext(i))->ping();


	for (unsigned int i = 0; i < transaction_interface->get_cant_pushbuttons(); i++)
		(transaction_interface->get_pushbutton(i))->ping();
}

void Simulation::triggerEnd(void) { end = true; }

ALLEGRO_DISPLAY* Simulation::getDisplay(void) { return display; }

bool Simulation::shouldEnd(void) { return end; }



Model_Transaction_GUI * 
Simulation::get_transaction_interface_gui()
{
	return this->transaction_interface;
}



bool
Simulation::attend_transaction(void)
{

	//valido a ver si la transaccion puede llegar a ser valida (hay id's validos y un monto posible)

	bool possible_tx = false;

	string from_node = this->transaction_interface->get_boxtext(TRANS_INTERF_EDITB1_NMBER)->get_actual_text();

	for (Node * node_attached : this->nodes) //chequeo from
	{
		if (node_attached->getNodeID() == from_node)
		{
			possible_tx = true;
		}
	}

	if (possible_tx == true) //hay from valido?
	{
		possible_tx = false;

		string to_node = this->transaction_interface->get_boxtext(TRANS_INTERF_EDITB2_NMBER)->get_actual_text();

		for (Node * node_attached : this->nodes) //chequeo "to"
		{
			if (node_attached->getNodeID() == to_node)
			{
				possible_tx = true;
			}
		}


	}

	if (possible_tx == true) //si paso from ok, hay "to" valido?
	{
		possible_tx = false; //chequeo amount

		string amount = this->transaction_interface->get_boxtext(TRANS_INTERF_EDITB3_NMBER)->get_actual_text();

		bool is_positive_number = (amount.find_first_not_of("0123456789.") == string::npos);

		size_t apparence_dot = std::count(amount.begin(), amount.end(), '.');



		if ((apparence_dot <= 1) && is_positive_number)
		{
			possible_tx = true;
		}

	}


	if (possible_tx == true) //si paso from, "to" ok, hay "amount" valido?
	{
		//hago la transaccion
	
		string from_node = this->transaction_interface->get_boxtext(TRANS_INTERF_EDITB1_NMBER)->get_actual_text();


		for (Node * node_attached : this->nodes) //chequeo from
		{
			if (node_attached->getNodeID() == from_node)
			{

				string to_node = this->transaction_interface->get_boxtext(TRANS_INTERF_EDITB2_NMBER)->get_actual_text();
				string amount = this->transaction_interface->get_boxtext(TRANS_INTERF_EDITB3_NMBER)->get_actual_text();

		#error "ACA ME QUEDE, NO SE SI TENGO QUE HACERR "node_attached->do_transaction()" bla bla o no, porque la misma, le quita la UTXO"


			}
		}




	}




}