#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <nlohmann/json.hpp>
#include "FullNode.h"
#include "SPVNode.h"
#include "MinerNode.h"
#include <windows.h>

#include "Simulation.h"
#include "RegularNodeView.h"
#include "SimView.h"
#include "Controller_Sim.h"

#include <vector>
#include <allegro5\allegro.h>
#include "Definitions.h"

//**
#include "Allegro.h"
#include "Controller.h"
//**


using namespace std;
using json = nlohmann::json;

#define TEN_SEC 10000
#define MINERNUM 3
#define FULLNUM	5
#define SPVNUM	5

// Aux Function
static void nodeFactory(int minerNum, int fullNum, vector<FullNode*>& fulls, int spvNum, vector<SPVNode*>& spvs, Simulation& sim, Controller_Sim& simCtrl);
static void teloParaNodos(vector<FullNode*>& fulls, vector<SPVNode*>& spvs); // el telo para nodos es donde van a hacer conexiones entre si ;)
bool getBlockChainJson(json* dest, const char* file);

int main()
{
	EventData ev_data{ nullptr, nullptr };


	ALLEGRO_TIMER* timer = NULL;
	ALLEGRO_EVENT_QUEUE* queue = initAllegro(timer);
	
	if (queue == nullptr)
	{
		cout << "Error in initialize Allegro" << endl;
		return 0;
	}
	else
		ev_data.event_queue = queue;

	Simulation sim(ev_data.event_queue);	// se crea el sujeto Simulation
	SimView* simulationView = new SimView;
	sim.attach(simulationView);
	Controller_Sim simCtrl(&sim);

	// aca va la factory***********************************
	vector<FullNode*> fulls;
	vector<SPVNode*> spvs;

	nodeFactory(MINERNUM, FULLNUM, fulls, SPVNUM, spvs, sim, simCtrl);

	teloParaNodos(fulls, spvs);

	vector<MerkleNode *> merkleTrees;
	json blockChainJson;

	if (getBlockChainJson(&blockChainJson, "test.json"))	//Se obtienen los bloques de "test.json"
	{
		int size = (unsigned int)blockChainJson.size();
		for (int i = 0; (i < size); i++)
		{
			json tempBlock = blockChainJson[i];			//Por cada bloque del json, se lo manda a los full nodes. 
			fulls[0]->recieveBlock(tempBlock);
			fulls[2]->recieveBlock(tempBlock);
			fulls[0]->sendInfo2Spv();
			fulls[2]->sendInfo2Spv();
			spvs[0]->pullHeaderfromFullNode();
		}
	}

	ALLEGRO_EVENT ev;
	ev_data.al_ev = &ev;
	al_start_timer(timer);

	while (!sim.shouldEnd())
	{
		if (!(al_is_event_queue_empty(ev_data.event_queue)))
		{
			al_get_next_event(ev_data.event_queue, ev_data.al_ev);
			simCtrl.dispatcher(&ev_data);
		}
	}

	destroyAllegro(ev_data.event_queue, timer);

	return 0;

	
}


bool getBlockChainJson(json* dest, const char* file)
{
	bool success = false;
	ifstream blockChainFile(file, ifstream::binary);
	if (blockChainFile) {

		blockChainFile.seekg(0, blockChainFile.end);
		int length = blockChainFile.tellg();
		blockChainFile.seekg(0, blockChainFile.beg);
		char * buffer = new char[length];
		blockChainFile.read(buffer, length);
		string strBuffer(buffer, length);
		delete[] buffer;

		*dest = json::parse(strBuffer);
		success = true;
	}
	return success;
}


static void nodeFactory(int minerNum, int fullNum, vector<FullNode*>& fulls, 
	int spvNum, vector<SPVNode*>& spvs, Simulation& sim, Controller_Sim& simCtrl)
{
	int totalNodeCount = fullNum + spvNum; // en este momento los mineros estan dentro de los full
	int fullPlusMiners = fullNum; // guardo un backup del numero de fulls (con mineros) para hacer cuentas
	fullNum -= minerNum; // separo los full de los mineros

	for (int i = 0; i < totalNodeCount; i++)
	{
		float posX = (GRAPH_RADIUS * cos(2 * M_PI*(i / (float)totalNodeCount)) + WIDTH_DEFAULT / 2.0) - RADIUS;
		float posY = (GRAPH_RADIUS * sin(2 * M_PI*(i / (float)totalNodeCount)) + HEIGHT_DEFAULT / 2.0) - RADIUS;

		if (((fullNum || minerNum) && ((((totalNodeCount / fullPlusMiners) == 1) && (i % 2 == 0)) || (((totalNodeCount / fullPlusMiners) != 1) && (i % (totalNodeCount / fullPlusMiners) == 0)))) || !spvNum) // medio complicada esta condicion, se podria acortar probablemente
		{
			if (fullNum)
			{
				string tempID = string("Full Node ") + to_string(fullNum);
				FullNode* tempFull = new FullNode(tempID);
				tempFull->setPos(posX, posY);
				RegularNodeView* tempView = new RegularNodeView(FULL_IMG_PATH);
				Controller_Node* tempControl = new Controller_Node(tempFull);
				tempFull->attach(tempView);
				sim.addNode(tempFull);
				simCtrl.addNodeController(tempControl);
				fulls.push_back(tempFull);
				fullNum--;
			}
			else if (minerNum)
			{
				string tempID = string("Miner Node ") + to_string(minerNum);
				MinerNode* tempMiner = new MinerNode(tempID);
				tempMiner->setPos(posX, posY);
				RegularNodeView* tempView = new RegularNodeView(MINER_IMG_PATH);
				Controller_Node* tempControl = new Controller_Node(tempMiner);
				tempMiner->attach(tempView);
				sim.addNode(tempMiner);
				simCtrl.addNodeController(tempControl);
				fulls.push_back(tempMiner);
				minerNum--;
			}
		}
		else if(spvNum)
		{
			string tempID = string("SPV Node ") + to_string(spvNum);
			SPVNode* tempSpv = new SPVNode(tempID);
			tempSpv->setPos(posX, posY);
			RegularNodeView* tempView = new RegularNodeView(SPV_IMG_PATH);
			Controller_Node* tempControl = new Controller_Node(tempSpv);
			tempSpv->attach(tempView);
			sim.addNode(tempSpv);
			simCtrl.addNodeController(tempControl);
			spvs.push_back(tempSpv);
			spvNum--;
		}
	}
}

static void teloParaNodos(vector<FullNode*>& fulls, vector<SPVNode*>& spvs)	// por ahora conecta hardcoded, hay que hacer el algoritmo
{
	fulls[0]->attachConnection(fulls[2]);
	fulls[2]->attachConnection(fulls[0]);
	fulls[0]->attachConnection(spvs[0]);
	fulls[2]->attachConnection(spvs[0]);
	spvs[0]->attachConnection(fulls[0]);
	spvs[0]->attachConnection(fulls[2]);
}