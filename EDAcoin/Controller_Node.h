#pragma once
#include "Controller.h"
#include "MinerNode.h"
#include "SPVNode.h"
#include "Controller_Blockchain.h"

class Controller_Node : public Controller
{
public:
	Controller_Node(Subject* creator);
	~Controller_Node();

	void parseMouseEvent(EventData * ev);
	void parseTransactionEvent(string& to, string& from, string& amount);
	void parseNetworkEvent(void);
	void parseKeyboardEvent(EventData * ev);
	void parseTimerEvent(EventData * ev);

	virtual void forwardMouseEvent(EventData* ev);
	virtual void forwardKeyboardEvent(EventData* ev);

private:

	Node* model;
	Controller_Blockchain* myBlockchainCtrl;

	void createBlockchainCtrl(void);
	bool clickInMe(EventData* ev);
};