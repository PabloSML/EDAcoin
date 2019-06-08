#pragma once

#include "Controller.h"

class Controller_MerkleTree : public Controller
{
	Controller_MerkleTree();
	~Controller_MerkleTree();

	void parseMouseEvent(EventData * ev);
	//void parseNetworkEvent(EventData * ev);
	void parseKeyboardEvent(EventData * ev);
	void parseTimerEvent(EventData * ev);



};