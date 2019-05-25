#pragma once
#include "Node.h"
#include "SPVNode.h"

class FullNode : public Node {

public:
	FullNode() : Node(string("Full Node")) {}
	~FullNode(){}

	void recieveBlock();
	void setFilter(SPVNode* filter);
	void requestLatestHeader();
	void requestHeaderCount();
	void requestHeader(int num);
	void getNextHeader();

	void sendInfo2Spv();
private:

};