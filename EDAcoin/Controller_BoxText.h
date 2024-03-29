#pragma once

#include "Controller.h"
#include "Model_BoxText.h"


class Controller_BoxText : public Controller
{
public:
	Controller_BoxText(Subject* creator);
	~Controller_BoxText();

	void parseMouseEvent(EventData * ev);
	void parseNetworkEvent(void){}
	void parseKeyboardEvent(EventData * ev);
	void parseTimerEvent(EventData * ev);
	void forwardKeyboardEvent(EventData * ev) {};
	void forwardMouseEvent(EventData * ev) {};

private:
	Model_BoxText* model;


	bool clickInMe(EventData* ev);

};