#pragma once
#include "Observer.h"
#include "Simulation.h"
#include <list>
#include <allegro5\allegro_color.h>
using namespace std;

class SimView : public Observer {
public:
	SimView(){}
	~SimView(){}

	void attach(Observer* view);
	bool detach(Observer* view);

	virtual void update(void* model);

	virtual void draw(void);

private:
	list<Observer*> views;
};