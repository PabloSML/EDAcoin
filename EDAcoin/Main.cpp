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

#include "Graph.h"
#include "Random.h"

#include <vector>
#include <allegro5\allegro.h>
#include "Definitions.h"

//**
#include "Allegro.h"
#include "Controller.h"
//**
#include "FormatConverter.h"


using namespace std;
using json = nlohmann::json;

#define TEN_SEC 10000
#define MINERNUM 3
#define FULLNUM	5
#define SPVNUM	5

// Aux Function
static void nodeFactory(int minerNum, int fullNum, vector<FullNode*>& fulls, int spvNum, vector<SPVNode*>& spvs, Simulation& sim, Controller_Sim& simCtrl);
static Graph* P2PNetworkGen(vector<FullNode*>& fulls, vector<SPVNode*>& spvs);
bool getBlockChainJson(json* dest, const char* file);


int main()
{
	randomize();
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

	vector<FullNode*> fulls;
	vector<SPVNode*> spvs;

	nodeFactory(MINERNUM, FULLNUM, fulls, SPVNUM, spvs, sim, simCtrl);

	sim.addAdjMatrix(P2PNetworkGen(fulls, spvs));

	json blockChainJson;

	if (getBlockChainJson(&blockChainJson, "test.json"))	//Se obtienen los bloques de "test.json"
	{
		int size = (unsigned int)blockChainJson.size();
		for (int i = 0; (i < size); i++)
		{
			json tempBlock = blockChainJson[i];			//Por cada bloque del json, se lo manda a los full nodes. 
			
			netPckg tempPckg{ tempBlock, fulls[0] };

			fulls[0]->analizePackage(tempPckg);
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


/*
int main()
{
	TransactionS t;
	t.txID = "AcaVaElID";
	InputS input;
	input.blockID = "IDdelBloque1";
	input.txID = "TrxnID1";
	t.inputs.push_back(input);
	input.blockID = "IDdelBloque2";
	input.txID = "TrxnID2";
	t.inputs.push_back(input);
	OutputS output;
	output.publicID = "PublicID";
	output.amount = 120;
	t.outputs.push_back(output);
	json j = Transactions2Json(t);
	cout << j << endl;
	cout << "..............." << endl;
	t = Json2Transactions(j);
	cout << "TxID:" << t.txID << endl;
	cout << "Inputs:" << endl;
	for (int i = 0; i < t.inputs.size(); i++)
	{
		cout << "BlockID:" << t.inputs[i].blockID << endl;
		cout << "TxID:" << t.inputs[i].txID << endl;
	}
	cout << "Outputs:" << endl;
	for (int i = 0; i < t.outputs.size(); i++)
	{
		cout << "PublicID:" << t.outputs[i].publicID << endl;
		cout << "Amount:" << t.outputs[i].amount << endl;
	}
	system("pause");
}
*/

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
				string tempID = string("FullNode") + to_string(fullNum);
				FullNode* tempFull = new FullNode(tempID);
				tempFull->setPos(posX, posY);
				RegularNodeView* tempView = new RegularNodeView(FULL_IMG_PATH);
				Controller_Node* tempControl = new Controller_Node(tempFull);
				tempFull->attach(tempView);
				simCtrl.addNodeController(tempControl);
				fulls.push_back(tempFull);
				fullNum--;
			}
			else if (minerNum)
			{
				string tempID = string("MinerNode") + to_string(minerNum);
				MinerNode* tempMiner = new MinerNode(tempID);
				tempMiner->setPos(posX, posY);
				RegularNodeView* tempView = new RegularNodeView(MINER_IMG_PATH);
				Controller_Node* tempControl = new Controller_Node(tempMiner);
				tempMiner->attach(tempView);
				simCtrl.addNodeController(tempControl);
				fulls.push_back(tempMiner);
				minerNum--;
			}
		}
		else if(spvNum)
		{
			string tempID = string("SPVNode") + to_string(spvNum);
			SPVNode* tempSpv = new SPVNode(tempID);
			tempSpv->setPos(posX, posY);
			RegularNodeView* tempView = new RegularNodeView(SPV_IMG_PATH);
			Controller_Node* tempControl = new Controller_Node(tempSpv);
			tempSpv->attach(tempView);
			simCtrl.addNodeController(tempControl);
			spvs.push_back(tempSpv);
			spvNum--;
		}
	}

	for (FullNode* F : fulls)	// se agregan a la sim en orden (primero fulls, luego spvs)
		sim.addNode(F);
	for (SPVNode* S : spvs)
		sim.addNode(S);
}

static Graph* P2PNetworkGen(vector<FullNode*>& fulls, vector<SPVNode*>& spvs)
{
	int fullCount = (int)(fulls.size());
	int spvCount = (int)(spvs.size());
	int totalCount = fullCount + spvCount;

	Graph* adjMatrix = new Graph(totalCount);

	for (int i = 0; i < fullCount; i++)		// recorre todos los fulls, eligiendo 2 otros fulls random y conectandolo si no esta conectado (llegando a un maximo de 2 conexiones)
	{
		FullNode* temp = fulls[i];
		int rndIndex1, rndIndex2;
		do {
			rndIndex1 = randIntBetween(0, fullCount - 1);
			rndIndex2 = randIntBetween(0, fullCount - 1);
		} while ( (rndIndex1 == i) || (rndIndex2 == i) || (rndIndex1 == rndIndex2) );

		FullNode* tempNeigh1 = fulls[rndIndex1];
		FullNode* tempNeigh2 = fulls[rndIndex2];

		if (adjMatrix->countEdges(i) < 2 && !(adjMatrix->isEdge(i, rndIndex1)))
		{
			temp->attachConnection(tempNeigh1);
			tempNeigh1->attachConnection(temp);
			adjMatrix->setEdge(i, rndIndex1);
		}

		if (adjMatrix->countEdges(i) < 2 && !(adjMatrix->isEdge(i, rndIndex2)))
		{
			temp->attachConnection(tempNeigh2);
			tempNeigh2->attachConnection(temp);
			adjMatrix->setEdge(i, rndIndex2);
		}
	}

	int randomChecker = randIntBetween(0, fullCount - 1);

	while (adjMatrix->BFSCount(randomChecker) < fullCount)	// si se cumple esta condicion significa que el grafo no es conexo, se elige un full al que no este conectado el checker y se lo conecta. Luego se repite el analisis
	{
		bool found = false;
		for (int i = 0; i < fullCount && !found; i++)
		{
			if ( (randomChecker != i) && !(adjMatrix->isEdge(randomChecker, i)) )
			{
				FullNode* checker = fulls[randomChecker];
				FullNode* temp = fulls[i];

				checker->attachConnection(temp);
				temp->attachConnection(checker);
				adjMatrix->setEdge(randomChecker, i);
				found = true;
			}
		}
	}

	for (int i = 0; i < spvCount; i++)		// se realiza la conexion entre cada spv y dos nodos full aleatorios
	{
		SPVNode* temp = spvs[i];
		int rndIndex1, rndIndex2;
		do {
			rndIndex1 = randIntBetween(0, fullCount - 1);
			rndIndex2 = randIntBetween(0, fullCount - 1);
		} while (rndIndex1 == rndIndex2);

		FullNode* tempNeigh1 = fulls[rndIndex1];
		FullNode* tempNeigh2 = fulls[rndIndex2];

		temp->attachConnection(tempNeigh1);
		tempNeigh1->attachConnection(temp);
		adjMatrix->setEdge(fullCount + i, rndIndex1);

		temp->attachConnection(tempNeigh2);
		tempNeigh2->attachConnection(temp);
		adjMatrix->setEdge(fullCount + i, rndIndex2);
	}

	return adjMatrix;
}