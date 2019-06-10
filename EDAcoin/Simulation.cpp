#include "Simulation.h"

Simulation::Simulation(ALLEGRO_EVENT_QUEUE* queue)
{
	display = al_create_display(WIDTH_DEFAULT, HEIGHT_DEFAULT);
	if (!display)
		cout << "Error creating sim display!" << endl;
	else
		al_register_event_source(queue, al_get_display_event_source(display));
}

Simulation::~Simulation(void)
{
	al_destroy_display(display);
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

void
Simulation::updateInsiderModels(void)
{
	for (Node* N : nodes)
		N->ping();
	for (Model_BoxText* TB : textBoxes)
		TB->ping();
	for (Model_PushButton* BU : buttons)
		BU->ping();
}

void Simulation::triggerEnd(void) { end = true; }

ALLEGRO_DISPLAY* Simulation::getDisplay(void) { return display; }

bool Simulation::shouldEnd(void) { return end; }

