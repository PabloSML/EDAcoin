#include "SimView.h"

void 
SimView::update(void* model)
{
	Simulation* simModel = (Simulation*)model;

	al_clear_to_color(al_color_name("aquamarine"));
	
	simModel->updateInsiderModels();
	
	al_flip_display();
}
