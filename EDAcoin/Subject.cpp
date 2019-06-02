#include "Subject.h"

void
Subject::attach(Observer* ptr)
{
	observers.push_back(ptr);
}

bool
Subject::detach(Observer* ptr)
{
	bool success = false;
	size_t currentSize = observers.size();

	observers.remove(ptr);

	if (currentSize - 1 == observers.size())	// verifica haber eliminado un elemento. Se puede sacar para eliminar las operaciones extra.
		success = true;

	return success;
}

void
Subject::notifyObservers(void)
{
	for (Observer* o : observers)
		o->update(this);
}