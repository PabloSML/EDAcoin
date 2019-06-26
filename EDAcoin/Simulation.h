#pragma once
#include <iostream>
#include <list>
#include "Subject.h"
#include "Node.h"
#include "Graph.h"
#include "Model_BoxText.h"
#include "Model_PushButton.h"

#include "Model_Transaction_GUI.h"

using namespace std;

class Simulation : public Subject {
public:
	Simulation(ALLEGRO_EVENT_QUEUE* queue);
	~Simulation();

	void addNode(Node* node);
	bool removeNode(Node* node);

	void addAdjMatrix(Graph* newMatrix);

	/*void addTextBox(Model_BoxText* box);
	bool removeTextBox(Model_BoxText* box);

	void addButton(Model_PushButton* button);
	bool removeButton(Model_PushButton* button);*/

	void updateInsiderModels(void);

	void triggerEnd(void);
	ALLEGRO_DISPLAY* getDisplay(void);
	bool shouldEnd(void);

	Model_Transaction_GUI * get_transaction_interface_gui();

	vector<pos_t> getNodesPos(void);
	Graph* getAdjMatrix(void);

	bool is_node_attached(string& node_id_wanted);
	string get_pbkey_node(string& node_id_wanted);

private:
	list<Node*> nodes;
	Graph* adjMatrix;
	//list<Model_BoxText*> textBoxes;
	//list<Model_PushButton*> buttons;
	bool end;
	ALLEGRO_DISPLAY* display;

	Model_Transaction_GUI * transaction_interface;

	bool init_ok;

};