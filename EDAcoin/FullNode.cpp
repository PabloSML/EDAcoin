#include "FullNode.h"

void
FullNode::attachConnection(Node* connection)
{
	connections.push_back(connection);
	Node* temp = connection->getFilter();
	if (temp != nullptr)
		filters.push_back((SPVNode*)connection);
}

void 
FullNode::dettachConnection(Node* connection)
{
	bool done = false;
	list<Node*>::iterator conecItr = connections.begin();
	int size = connections.size();
	for (int i = 0; i < size && !done; i++, conecItr++)
	{
		if (*conecItr == connection)
		{
			connections.erase(conecItr);
			done = true;
		}
	}

	done = false;
	list<SPVNode*>::iterator filterItr = filters.begin();
	size = filters.size();
	for (int i = 0; i < size && !done; i++, filterItr++)
	{
		if (*filterItr == (SPVNode*)connection)
		{
			filters.erase(filterItr);
			done = true;
		}
	}
}

void 
FullNode::recieveBlock()
{

}
void
FullNode::requestLatestHeader()
{

}

void 
FullNode::requestHeaderCount()
{

}
void 
FullNode::requestHeader(int num)
{

}
void 
FullNode::getNextHeader()
{

}
void
FullNode::sendInfo2Spv()
{

}