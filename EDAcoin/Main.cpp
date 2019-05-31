#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "FullNode.h"
#include "SPVNode.h"
#include <windows.h>



#include <vector>
#include <allegro5\allegro.h>
#include "Supervisor.h"
#include "Board.h"
#include "Viewer.h"
#include "Definitions.h"
#include "General_Controller.h"



using namespace std;
using json = nlohmann::json;

#define TEN_SEC 10000

// Aux Function

bool init_resources(void);
bool getBlockChainJson(json* dest, const char* file);

int main()
{
	//Se crean los nodos (en la faseI se nesesitan dos fullnodes y un spvnode).
	FullNode f1(string("FullNode One")), f2(string("FullNode Two"));
	SPVNode s1(string("SPVNode One"));
	//Se conectan los fullnodes con los spvnodes y entre ellos
	//	f1 <-> f2
	//	  \  /
	//	   \/	
	//	   s1


	
	

	bool init = init_resources();


	if (init)
	{
		General_Controller controller;

		supervisor super(controller.get_viewer());
		controller.set_supervisor(super);

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
			for (int i = 0; (i < size) && (!controller.is_finish()); i++)
			{
				json tempBlock = blockChainJson[i];			//Por cada bloque del json, se lo manda a los full nodes. 
				f1.recieveBlock(tempBlock);
				f2.recieveBlock(tempBlock);
				f1.sendInfo2Spv();
				f2.sendInfo2Spv();
				s1.pullHeaderfromFullNode();

				merkleTrees = f1.get_merkle_trees();

				controller.update(f1.get_blockChain(), merkleTrees);

				unsigned long index = 20000000;

				while (index && !(controller.is_finish()))
				{
					controller.dispatcher();
					index--;
				}
			}

			controller.update(f1.get_blockChain(), merkleTrees);

			while (controller.is_finish() == false)
			{
				controller.dispatcher();

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
		//string strBuffer = string("");
		blockChainFile.read(buffer, length);
		//for (int i = 0; i < length; i++)
		//	strBuffer.push_back(buffer[i]);
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