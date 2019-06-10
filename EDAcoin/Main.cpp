#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "FullNode.h"
#include "SPVNode.h"
#include <windows.h>

#include "Simulation.h"
#include "RegularNodeView.h"
#include "SimView.h"

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

// Aux Function

bool init_resources(void);
bool getBlockChainJson(json* dest, const char* file);

int main()
{
	/*
	//**Ejemplo de la inicializacion de allegro.
	EventData ev_data;
	ALLEGRO_EVENT_QUEUE* queue = initAllegro();
	if (queue == nullptr)
	{
		cout << "Error in initialize Allegro" << endl;
		return 0;
	}
	else
		ev_data.event_queue = queue;
	*/


	bool init = init_resources();

	if (init)
	{
		

		Simulation sim;	// se crea el sujeto Simulation
		SimView simulationView;
		sim.attach(&simulationView);

		//Se crean los nodos (en la faseI se nesesitan dos fullnodes y un spvnode).
		FullNode f1("FullNode One"), f2("FullNode Two");
		SPVNode s1("SPV Node");

		RegularNodeView f1RView(FULL_IMG_PATH); // se crean las views base de cada nodo		LA POSICION ESTA HARDCODEADA PORQUE NO EXISTE AUN UNA FUNCION FACTORY QUE CREE TODO EN LUGARES APROPIADOS!!!!!
		RegularNodeView f2RView(FULL_IMG_PATH);
		RegularNodeView s1RView(SPV_IMG_PATH);

		f1.attach(&f1RView); // se conectan los observers a los subjects
		f2.attach(&f2RView);
		s1.attach(&s1RView);

		sim.addNode(&f1); // se agregan los nodos a la lista de la simulacion
		sim.addNode(&f2);
		sim.addNode(&s1);

		//simulationView.attach(&f1RView);
		//simulationView.attach(&f2RView);
		//simulationView.attach(&s1RView);
		//**cada vez que hace el attach, llama a draw????

	//Se conectan los fullnodes con los spvnodes y entre ellos
	//	f1 <-> f2
	//	  \  /
	//	   \/	
	//	   s1
		f1.attachConnection(&f2);
		f1.attachConnection(&s1);
		f2.attachConnection(&f1);
		f2.attachConnection(&s1);
		s1.attachConnection(&f1);
		s1.attachConnection(&f2);

		vector<MerkleNode *> merkleTrees;
		json blockChainJson;

		if (getBlockChainJson(&blockChainJson, "test.json"))	//Se obtienen los bloques de "test.json"
		{

			int size = (unsigned int)blockChainJson.size();
			for (int i = 0; (i < size); i++)
			{
				json tempBlock = blockChainJson[i];			//Por cada bloque del json, se lo manda a los full nodes. 
				f1.recieveBlock(tempBlock);
				f2.recieveBlock(tempBlock);
				f1.sendInfo2Spv();
				f2.sendInfo2Spv();
				s1.pullHeaderfromFullNode();

				merkleTrees = f1.get_merkle_trees();


				//No es necesario para el MVC porque no deberia mostrar la blockchain.
				unsigned long index = 20000000;

			}

		
		}

		return 0;
	}
	else
	{
		return 1;
	}
	
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

bool init_resources(void)
{
	bool init = true;
	
	if (!al_init())
	{
		init = false;
	}
	else
	{
		if (!al_install_keyboard())
		{
			init = false;
		}
		else
		{
			if ((!al_install_mouse()))
			{
				init = false;
			}
		}

	}

	
	return init;
}