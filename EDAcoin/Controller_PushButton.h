#pragma once

#include "Controller.h"
#include "Model_PushButton.h"


class Controller_PushButton: public Controller
{
public:
	Controller_PushButton(Subject* creator);
	~Controller_PushButton();

	void parseMouseEvent(EventData * ev);
	//void parseNetworkEvent(EventData * ev);
	void parseKeyboardEvent(EventData * ev);
	void parseTimerEvent(EventData * ev);
	void forwardKeyboardEvent(EventData * ev) {};
	void forwardMouseEvent(EventData * ev) {};

private:
	Model_PushButton* model;
	
	
	bool clickInMe(EventData* ev);

};