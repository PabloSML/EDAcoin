#pragma once

#include "Controller.h"
#include "MerkleNode.h"

class Controller_Block : public Controller
{
public:
	Controller_Block();
	~Controller_Block();

	void parseMouseEvent(EventData * ev);
	//void parseNetworkEvent(EventData * ev);
	void parseKeyboardEvent(EventData * ev);
	void parseTimerEvent(EventData * ev);

	void recieveMouseEv(EventData* ev, MerkleNode* tree);

};