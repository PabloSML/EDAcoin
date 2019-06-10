#include "SimView.h"

SimView::SimView(void)
{
	display = al_create_display(WIDTH_DEFAULT, HEIGHT_DEFAULT);
	if (!display)
		cout << "Error creating sim display!" << endl;
}

SimView::~SimView(void)
{
	al_destroy_display(display);
}

void 
SimView::update(void* model)
{
	Simulation* simModel = (Simulation*)model;

	al_clear_to_color(al_color_name("aquamarine"));
	
	simModel->updateInsiderModels();
	
	al_flip_display();
}
