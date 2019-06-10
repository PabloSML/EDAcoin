#pragma once
#include <vector>
#include "Controller.h"

#include "Controller_Node.h"
#include "Simulation.h"
using namespace std;

class Controller_Sim : public Controller {

public:
	Controller_Sim(Simulation* owner);
	~Controller_Sim();

	virtual void parseMouseEvent(EventData * ev);
	//virtual void parseNetworkEvent(EventData * ev);
	virtual void parseKeyboardEvent(EventData * ev);
	virtual void parseTimerEvent(EventData * ev);

	bool shouldModelDie(void);


private:
	Simulation* model;
	vector<Controller_Node*> nodeControllers;

	bool isThisMine(EventData* ev);
};
