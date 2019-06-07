#pragma once
#include <list>
#include "Subject.h"
#include "Node.h"
#include "Model_BoxText.h"
#include "Model_PushButton.h"
using namespace std;

class Simulation : public Subject {
public:
	Simulation(){}
	~Simulation(){}

	void attachNode(Node* node);
	bool detachNode(Node* node);

private:
	list<Node*> nodes; //aca no iria vector??? por?
	list<Model_BoxText*> textBoxes;
	list<Model_PushButton*> buttons;
};