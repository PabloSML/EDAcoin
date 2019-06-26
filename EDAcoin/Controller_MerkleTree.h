#pragma once

#include "Model_MerkleTree.h"
#include "Controller.h"

class Controller_MerkleTree : public Controller
{
public:
	Controller_MerkleTree(Subject* creator);
	~Controller_MerkleTree();

	void parseMouseEvent(EventData * ev);
	void parseNetworkEvent(void){}
	void parseKeyboardEvent(EventData * ev);
	void parseTimerEvent(EventData * ev);

	virtual void forwardMouseEvent(EventData* ev);
	virtual void forwardKeyboardEvent(EventData* ev);

	bool shouldModelDie(void);

private:
	Model_MerkleTree* model;
	bool isThisMine(EventData* ev);
};