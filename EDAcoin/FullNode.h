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

	virtual void attachConnection(Node* connection);
	virtual void dettachConnection(Node* connection);

	virtual Node* getFilter(void) { return nullptr; }

	void sendInfo2Spv();
private:
	list<SPVNode*> filters;
};