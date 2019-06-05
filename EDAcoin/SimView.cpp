#include "SimView.h"

void 
SimView::update(void* model)
{
	Simulation* simModel = (Simulation*)model;

	al_clear_to_color(al_color_name("aquamarine"));
	
	for (Observer* o : views)
	{
		o->update(this);
	}
	al_flip_display();
}

void
SimView::attach(Observer* view)
{
	views.push_back(view);
	draw();
}

bool
SimView::detach(Observer* view)
{
	bool success = false;
	size_t currentSize = views.size();

	views.remove(view);

	if (currentSize - 1 == views.size())	// verifica haber eliminado un elemento. Se puede sacar para eliminar las operaciones extra.
	{
		success = true;
		draw();
	}

	return success;
}

