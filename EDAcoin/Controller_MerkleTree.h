#pragma once

#include "Model_MerkleTree.h"
#include "Controller.h"

class Controller_MerkleTree : public Controller
{
public:
	Controller_MerkleTree();
	~Controller_MerkleTree();

	void parseMouseEvent(EventData * ev);
	//void parseNetworkEvent(EventData * ev);
	void parseKeyboardEvent(EventData * ev);
	void parseTimerEvent(EventData * ev);


private:
	Model_MerkleTree* model;
};