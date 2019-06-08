#include "Subject.h"

void
Subject::attach(Observer* ptr)
{
	observers.push_back(ptr);
	notifyObservers();
}

bool
Subject::dettach(Observer* ptr)
{
	bool success = false;
	size_t currentSize = observers.size();

	observers.remove(ptr);

	if (currentSize - 1 == observers.size())	// verifica haber eliminado un elemento. Se puede sacar para eliminar las operaciones extra.
	{
		success = true;
		notifyObservers();
	}

	return success;
}

void
Subject::ping(void)
{
	notifyObservers();
}

void
Subject::notifyObservers(void)
{
	for (Observer* o : observers)
		o->update(this);
}

Subject::~Subject(void)
{
	for (Observer* o : observers)
		delete o;
}