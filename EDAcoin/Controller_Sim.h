#pragma once
#include <vector>
#include <list>
#include "Controller.h"

#include "Controller_Node.h"
#include "Simulation.h"

#include "Controller_Transaction_GUI.h"


using namespace std;

class Controller_Sim : public Controller {

public:
	Controller_Sim(Simulation* owner, ALLEGRO_TIMER* evTimer, ALLEGRO_TIMER* netTimer);
	~Controller_Sim();

	void dispatcher(EventData* ev);

	void addNodeController(Controller_Node* nodeCtrl);
	bool removeNodeController(Controller_Node* nodeCtrl);
	void removeAllNodeCtrl(void);

	virtual void parseMouseEvent(EventData * ev);
	virtual void parseNetworkEvent(void);
	virtual void parseKeyboardEvent(EventData * ev);
	virtual void parseTimerEvent(EventData * ev);

	virtual void forwardMouseEvent(EventData* ev) {}
	virtual void forwardKeyboardEvent(EventData* ev) {}

	bool shouldModelDie(void);


private:
	Simulation* model;
	list<Controller_Node*> nodeControllers;
	
	Controller_Transaction_GUI * controller_transaction_gui;

	ALLEGRO_TIMER* evTimer;
	ALLEGRO_TIMER* netTimer;

	bool isThisMine(EventData* ev);

	void attend_transaction(void);



};
