#include "Simulation.h"

void
Simulation::attachNode(Node* node)
{
	nodes.push_back(node);
	notifyObservers();
}

bool
Simulation::detachNode(Node* node)
{
	bool success = false;
	size_t currentSize = nodes.size();

	nodes.remove(node);

	if (currentSize - 1 == nodes.size())
		success = true;

	return success;
}