#include "Simulation.h"

void
Simulation::attach(Node* node)
{
	nodes.push_back(node);
}

bool
Simulation::detach(Node* node)
{
	bool success = false;
	size_t currentSize = nodes.size();

	nodes.remove(node);

	if (currentSize - 1 == nodes.size())
		success = true;

	return success;
}