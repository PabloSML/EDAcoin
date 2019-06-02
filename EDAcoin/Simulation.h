#pragma once
#include <list>
#include "Subject.h"
#include "Node.h"
using namespace std;

class Simulation : public Subject {
public:
	Simulation(){}
	~Simulation(){}

	void attach(Node* node);
	bool detach(Node* node);

private:
	list<Node*> nodes;
};