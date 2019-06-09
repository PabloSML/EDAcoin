#pragma once
#include "Controller.h"
#include "Node.h"
#include "Controller_Blockchain.h"

class Controller_Node : public Controller
{
public:
	Controller_Node(Subject* creator);
	~Controller_Node();

	void parseMouseEvent(EventData * ev);
	//void parseNetworkEvent(EventData * ev);
	void parseKeyboardEvent(EventData * ev);
	void parseTimerEvent(EventData * ev);


private:

	Node* model;
	Controller_Blockchain* myBlockchainCtrl;

	bool isThisMine(EventData* ev);
	void createBlockchainCtrl(void);
	bool clickInMe(EventData* ev);
};