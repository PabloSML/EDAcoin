#include "SimView.h"

void 
SimView::update(void* model)
{
	Simulation* simModel = (Simulation*)model;

	al_set_target_backbuffer(simModel->getDisplay());

	al_clear_to_color(al_color_name("aquamarine"));
	
	simModel->updateInsiderModels();
	
	al_set_target_backbuffer(simModel->getDisplay());

	al_flip_display();
}
