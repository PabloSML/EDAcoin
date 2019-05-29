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


void display_stuff(json& blockChainJson, vector<MerkleNode *> merkle_trees);


using namespace std;
using json = nlohmann::json;

#define TEN_SEC 10000

// Aux Function
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
		int size = (unsigned int) blockChainJson.size();
		for (int i = 0; i < size; i++)
		{
			json tempBlock = blockChainJson[i];			//Por cada bloque del json, se lo manda a los full nodes. 
			f1.recieveBlock(tempBlock);
			f2.recieveBlock(tempBlock);
			f1.sendInfo2Spv();
			f2.sendInfo2Spv();
			s1.pullHeaderfromFullNode();

			merkleTrees = f1.get_merkle_trees();

			Sleep(100);
		}
		
		display_stuff(blockChainJson, merkleTrees);

	}

	return 0;
}

void display_stuff(json& blockChainJson, vector<MerkleNode *> merkle_trees)
{
	//bloques

	bool all_ok = true;
	

	if (!al_init())
	{
		cout << "Allegro Failed to initialize" << endl;
	}
	else
	{

		viewer view;

		vector<ImageDescriptor> block_images;
		vector<ImageDescriptor> buttons;

		for (int i = 0; i < ((int)blockChainJson.size()); i++)
		{
			ImageDescriptor image(IMAGE_BLOCK_PATH); //init de todas las imagenes
			block_images.push_back(image);
			
		}

	
		ImageDescriptor button_left(PATH_BUTTON_LEFT); //init de los botones
		ImageDescriptor button_right(PATH_BUTTON_RIGHT);

		buttons.push_back(button_left);
		buttons.push_back(button_right);

		board boar(WIDTH_DEFAULT, HEIGHT_DEFAULT, block_images, buttons, merkle_trees);

		if (boar.is_images_error())
		{
			cout << "Image initialization Failed" << endl;
			all_ok = ERROR;
		}

		boar.set_image_size(IMAGE_SIZE_X, IMAGE_SIZE_Y);

		boar.refresh();

		view.update_display(boar);

		al_set_target_backbuffer(view.get_display());

		al_flip_display();

		if (!(view.is_init()))
		{
			cout << "Viewer Failed to initialize" << endl;
			all_ok = ERROR;
		}

		supervisor superv(view);

		while (!(superv.is_finish()))
		{
			superv.dispatcher(view, boar);
		}

		block_images.erase(block_images.begin());
		buttons.erase(buttons.begin());
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