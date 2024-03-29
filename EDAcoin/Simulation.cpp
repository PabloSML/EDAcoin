#include "Simulation.h"
#include "Definitions.h"
#include "MerkleNode.h"

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
		delete adjMatrix;
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

void
Simulation::addAdjMatrix(Graph* newMatrix)
{
	adjMatrix = newMatrix;
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

vector<pos_t> Simulation::getNodesPos(void)
{
	vector<pos_t> v;
	pos_t pos;
	for (Node* n : this->nodes)
	{
		pos = n->getPos();
		v.push_back(pos);
	}
	return v;
}


Graph* Simulation::getAdjMatrix(void)
{
	return this->adjMatrix;
}



bool 
Simulation::is_node_attached(string& node_id_wanted)
{
	bool is_there = false;

	for (Node * n : (this->nodes))
	{
		if (node_id_wanted == n->getNodeID())
		{
			is_there = true;
			break;
		}
	}

	return is_there;
}
string 
Simulation::get_pbkey_node(string& node_id_wanted)
{

	string ret;

	for (Node * n : (this->nodes))
	{
		if (node_id_wanted == n->getNodeID())
		{
			ret = n->getStringPubKey();
			break;
		}
	}

	return ret;
}