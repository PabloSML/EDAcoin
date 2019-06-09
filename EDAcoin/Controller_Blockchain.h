#pragma once
#include <vector>
#include "Controller.h"
#include "Model_Blockchain.h"
#include "Controller_Block.h"
using namespace std;

class Controller_Blockchain : public Controller {

public:
	Controller_Blockchain(Model_Blockchain* owner);
	~Controller_Blockchain();

	virtual void parseMouseEvent(EventData * ev);
	//virtual void parseNetworkEvent(EventData * ev);
	virtual void parseKeyboardEvent(EventData * ev);
	virtual void parseTimerEvent(EventData * ev);

	bool shouldModelDie(void);


private:
	Model_Blockchain* model;
	vector<Controller_Block*> blockControllers;

	bool isThisMine(EventData* ev);
};
