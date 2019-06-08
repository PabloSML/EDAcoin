#include "Controller_Blockchain.h"

Controller_Blockchain::Controller_Blockchain(Model_Blockchain* creator)
{
	model = creator;
}

Controller_Blockchain::~Controller_Blockchain(void)
{
	for (Controller_Block* C : blockControllers)
		delete C;
}

void
Controller_Blockchain::parseMouseEvent(EventData* ev)
{
	if (model->can_show_merkle_trees())
	{
		for (int i = 0; i < (int)blockControllers.size(); i++)
		{
			MerkleNode* tree = model->getMerkleTree(i);
			blockControllers[i]->recieveEvent(ev, tree);	// recieve event tiene que estar en Controller_Block y tiene que llamar a parseMouseEvent con el ev y tiene el tree por si lo necesita
		}
	}
}

