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
	//void parseNetworkEvent(EventData * ev);
	void parseKeyboardEvent(EventData * ev);
	void parseTimerEvent(EventData * ev);

	void recieveMouseEv(EventData* ev, MerkleNode* tree);


private:
	Model_Block* model;
	Controller_MerkleTree* myMerkleTreeCtrl;

	bool isThisMine(EventData* ev);
	void createMerkleTreeCtrl(void);
	bool clickInMe(EventData* ev);
};