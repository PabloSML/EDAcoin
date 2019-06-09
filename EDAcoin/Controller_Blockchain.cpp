#include "Controller_Blockchain.h"

Controller_Blockchain::Controller_Blockchain(Model_Blockchain* owner) : Controller(owner)
{
	Subject* subj = this->get_subject_attach();
	model = (Model_Blockchain *)subj;
}

Controller_Blockchain::~Controller_Blockchain(void)
{
	for (Controller_Block* C : blockControllers)
		delete C;
}

void
Controller_Blockchain::parseMouseEvent(EventData* ev)
{
	if (isThisMine(ev)) // si el evento fue en la pantalla de bchain, se ve si fue un evento de close o se clickeo en algun block
	{
		if (ev->al_ev->type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			model->triggerEnd();
		}

		else if (model->can_show_merkle_trees())  // si este modelo no puede mostrar trees, se ignora lo siguiente
		{
			for (int i = 0; i < (int)blockControllers.size(); i++)
			{
				MerkleNode* tree = model->getMerkleTree(i);
				blockControllers[i]->recieveMouseEv(ev, tree);
			}
		}
	}
	else // si el evento no fue en la pantalla de bchain, se sabe que es de merkleTree y pasa directo
	{
		for (Controller_Block* C : blockControllers)
			C->parseMouseEvent(ev);
	}
}

void
Controller_Blockchain::parseKeyboardEvent(EventData* ev) // nothing
{

}

void
Controller_Blockchain::parseTimerEvent(EventData* ev)
{
	if (this->is_subject_attached == true)
	{
		unsigned int blockCount = model->getBlockCount();	// cuantos blocks hay?
		unsigned int pending = model->recountBlocks();	// cuantos nuevos hay ahora? (se refresca la blockChain del modelo)
		for (unsigned int i = blockCount; i < blockCount + pending; i++)	// por cada nuevo se le asigna un controller y se pushea a la lista
		{
			Controller_Block* tempController = new Controller_Block(model->getBlockbyIndex(i));
			blockControllers.push_back(tempController);
		}
		model->ping();
		for (Controller_Block* C : blockControllers)
			C->parseTimerEvent(ev);
	}
}

bool
Controller_Blockchain::isThisMine(EventData* ev)
{
	ALLEGRO_DISPLAY* evDisplay = ev->al_ev->display.source;
	ALLEGRO_DISPLAY* myDisplay = model->getDisplay();

	if (evDisplay == myDisplay)
		return true;
	else
		return false;
}