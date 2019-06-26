#pragma once

#include "Controller.h"
#include "Model_Button_Blockchain.h"


class Controller_Button_Blockchain : public Controller
{
public:
	Controller_Button_Blockchain(Subject* creator);
	~Controller_Button_Blockchain();

	void parseMouseEvent(EventData * ev);
	void parseNetworkEvent(void){}
	void parseKeyboardEvent(EventData * ev);
	void parseTimerEvent(EventData * ev);
	void forwardKeyboardEvent(EventData * ev) {};
	void forwardMouseEvent(EventData * ev) {};

	bool clickInMe(EventData* ev);


private:
	Model_Button_Blockchain* model;



};