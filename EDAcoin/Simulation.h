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

	void addNode(Node* node);
	bool removeNode(Node* node);

	void addTextBox(Model_BoxText* box);
	bool removeTextBox(Model_BoxText* box);

	void addButton(Model_PushButton* button);
	bool removeButton(Model_PushButton* button);

	void updateInsiderModels(void);

	void triggerEnd(void);
	ALLEGRO_DISPLAY* getDisplay(void);
	bool shouldEnd(void);



private:
	list<Node*> nodes; //aca no iria vector??? por?
	list<Model_BoxText*> textBoxes;
	list<Model_PushButton*> buttons;
	bool end;
	ALLEGRO_DISPLAY* display;


};