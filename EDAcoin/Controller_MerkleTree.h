#pragma once

#include "Model_MerkleTree.h"
#include "Controller.h"

class Controller_MerkleTree : public Controller
{
public:
	Controller_MerkleTree(Subject* creator);
	~Controller_MerkleTree();

	void parseMouseEvent(EventData * ev);
	//void parseNetworkEvent(EventData * ev);
	void parseKeyboardEvent(EventData * ev);
	void parseTimerEvent(EventData * ev);

	bool shouldModelDie(void);

private:
	Model_MerkleTree* model;
	bool isThisMine(EventData* ev);
};