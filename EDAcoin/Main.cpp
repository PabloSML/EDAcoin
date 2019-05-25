#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "FullNode.h"
#include "SPVNode.h"
using namespace std;
using json = nlohmann::json;

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
		// magic stuff
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