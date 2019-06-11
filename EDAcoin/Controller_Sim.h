#pragma once
#include <vector>
#include <list>
#include "Controller.h"

#include "Controller_Node.h"
#include "Simulation.h"
using namespace std;

class Controller_Sim : public Controller {

public:
	Controller_Sim(Simulation* owner);
	~Controller_Sim();

	void dispatcher(EventData* ev);

	void addNodeController(Controller_Node* nodeCtrl);
	bool removeNodeController(Controller_Node* nodeCtrl);
	void removeAllNodeCtrl(void);

	virtual void parseMouseEvent(EventData * ev);
	//virtual void parseNetworkEvent(EventData * ev);
	virtual void parseKeyboardEvent(EventData * ev);
	virtual void parseTimerEvent(EventData * ev);

	virtual void forwardMouseEvent(EventData* ev) {}
	virtual void forwardKeyboardEvent(EventData* ev) {}

	bool shouldModelDie(void);


private:
	Simulation* model;
	list<Controller_Node*> nodeControllers;

	bool isThisMine(EventData* ev);
};
