#pragma once
#include <vector>
#include "Controller.h"

#include "Model_Transaction_GUI.h"
#include "Controller_PushButton.h"
#include "Controller_BoxText.h"

class Controller_Transaction_GUI : public Controller
{
	public:
		Controller_Transaction_GUI(Model_Transaction_GUI* owner);
		~Controller_Transaction_GUI();

		virtual void parseMouseEvent(EventData * ev);
		//virtual void parseNetworkEvent(EventData * ev);
		virtual void parseKeyboardEvent(EventData * ev);
		virtual void parseTimerEvent(EventData * ev);

		virtual void forwardMouseEvent(EventData* ev);
		virtual void forwardKeyboardEvent(EventData* ev);


	private:


		Model_Transaction_GUI* model;

		vector<Controller_PushButton*> pushButtons_controllers;
		vector<Controller_BoxText*>	   edittexts_controllers;

		bool isThisMine(EventData* ev);


};