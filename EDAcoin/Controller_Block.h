#pragma once

#include "Controller.h"
#include "MerkleNode.h"
#include "Model_Block.h"
#include "Controller_MerkleTree.h"

class Controller_Block : public Controller
{
public:
	Controller_Block(Subject* owner);
	~Controller_Block();

	void parseMouseEvent(EventData * ev);
	void parseMouseEvent(EventData * ev, MerkleNode* tree);
	//void parseNetworkEvent(EventData * ev);
	void parseKeyboardEvent(EventData * ev);
	void parseTimerEvent(EventData * ev);

	virtual void forwardMouseEvent(EventData* ev);
	virtual void forwardKeyboardEvent(EventData* ev);

private:
	Model_Block* model;
	Controller_MerkleTree* myMerkleTreeCtrl;

	void createMerkleTreeCtrl(void);
	bool clickInMe(EventData* ev);


};