#include "Controller_Block.h"
#include <list>
#include "Subject.h"



using namespace std;

Controller_Block::
Controller_Block(Subject* owner) : Controller(owner), myMerkleTreeCtrl(nullptr)
{
	Subject* subj = this->get_subject_attach();
	model = (Model_Block *)subj;
}

Controller_Block::
~Controller_Block()
{
	if (myMerkleTreeCtrl != nullptr)
		delete myMerkleTreeCtrl;
}

void Controller_Block::
parseTimerEvent(EventData * ev) //refresh
{
	if (this->is_subject_attached == true)
	{
		model->ping();
		if(myMerkleTreeCtrl != nullptr)
			myMerkleTreeCtrl->parseTimerEvent(ev);
	}
}


void Controller_Block::
parseMouseEvent(EventData * ev)
{
	if (myMerkleTreeCtrl != nullptr)
	{
		myMerkleTreeCtrl->parseMouseEvent(ev);
		if (myMerkleTreeCtrl->shouldModelDie())	// el evento puede haber sido de Close
		{
			model->destroyMerkleTreeModel();
			if (myMerkleTreeCtrl != nullptr)
			{
				delete myMerkleTreeCtrl;
				myMerkleTreeCtrl = nullptr;
			}
		}
	}
}

void Controller_Block::
parseKeyboardEvent(EventData * ev) //nothing
{

}


void
Controller_Block::recieveMouseEv(EventData* ev, MerkleNode* tree)
{
	if (isThisMine(ev))
	{
		if (clickInMe(ev))	// se evalua despues ya que si el click fue en el display apropiado pero en otro lado no hay que pasar el ev mas adelante
		{
			model->createMerkleTreeModel(tree);	// tener en cuenta que ninguno de estos metodos crea si ya habia algo de antes
			createMerkleTreeCtrl();
		}
	}
}

bool
Controller_Block::isThisMine(EventData* ev)
{
	ALLEGRO_DISPLAY* evDisplay = ev->al_ev->mouse.display;
	ALLEGRO_DISPLAY* myDisplay = model->getEnviroment();

	if (evDisplay == myDisplay)
		return true;
	else
		return false;
}

void
Controller_Block::createMerkleTreeCtrl(void)
{
	if (myMerkleTreeCtrl == nullptr)
	{
		myMerkleTreeCtrl = new Controller_MerkleTree(model->getMerkleTreeModel());
	}
}

bool
Controller_Block::clickInMe(EventData* ev)
{
	int myPosX = model->get_pos_x();
	int myPosY = model->get_pos_y();
	int limitX = myPosX + model->get_size_x();
	int limitY = myPosY + model->get_size_y();
	int clickPosX = ev->al_ev->mouse.x;
	int clickPosY = ev->al_ev->mouse.y;

	if (clickPosX >= myPosX && clickPosX <= limitX && clickPosY >= myPosY && clickPosY <= limitY)	// checkea si el click fue en el rango de la imagen
		return true;
	else
		return false;
}