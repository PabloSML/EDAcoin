#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "FullNode.h"
#include "SPVNode.h"
using namespace std;
using json = nlohmann::json;

#define TEN_SEC 10000

// Aux Function
bool getBlockChainJson(json* dest, const char* file);

int main()
{
	FullNode f1(string("FullNode One")), f2(string("FullNode Two"));
	SPVNode s1(string("SPVNode One"));
	f1.attachConnection(&f2);
	f1.attachConnection(&s1);
	f2.attachConnection(&f1);
	f2.attachConnection(&s1);
	s1.attachConnection(&f1);
	s1.attachConnection(&f2);

	json blockChainJson;

	if (getBlockChainJson(&blockChainJson, "test.json"))
	{
		int size = (unsigned int) blockChainJson.size();
		for (int i = 0; i < size; i++)
		{
			json tempBlock = blockChainJson[i];
			f1.recieveBlock(tempBlock);
			f2.recieveBlock(tempBlock);
			f1.sendInfo2Spv();
			f2.sendInfo2Spv();
			s1.pullHeaderfromFullNode();

			_sleep(TEN_SEC);
		}
		// magic stuff (display stuff)
	}

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
		string strBuffer = string("");
		blockChainFile.read(buffer, length);
		for (int i = 0; i < length; i++)
			strBuffer.push_back(buffer[i]);
		delete[] buffer;

		*dest = json::parse(strBuffer);
		success = true;
	}
	return success;
}