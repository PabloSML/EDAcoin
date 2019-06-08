#pragma once

#include "Controller.h"

class Controller_Block : public Controller
{
	Controller_Block();
	~Controller_Block();

	void parseMouseEvent(EventData * ev);
	//void parseNetworkEvent(EventData * ev);
	void parseKeyboardEvent(EventData * ev);
	void parseTimerEvent(EventData * ev);

};