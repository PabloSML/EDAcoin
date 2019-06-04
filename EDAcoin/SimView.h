#pragma once
#include "Observer.h"
#include "Simulation.h"

class SimView : public Observer {
public:
	SimView(){}
	~SimView(){}

	virtual void update(void* model);
};