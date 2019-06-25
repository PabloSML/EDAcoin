#pragma once
#include "Observer.h"
#include "Simulation.h"
#include <list>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5\allegro_color.h>
#include <allegro5/allegro_primitives.h>
using namespace std;

class SimView : public Observer {
public:
	SimView(){}
	~SimView(){}

	virtual void update(void* model);

	ALLEGRO_DISPLAY* getDisplay(void) { return display; }

private:
	ALLEGRO_DISPLAY* display;
	void drawConnections(vector<pos_t> v, Graph* g);
};