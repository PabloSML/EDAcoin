#include "Node.h"

bool
Node::dettachConnection(Node* connection)
{
	bool success = false;
	size_t currentSize = connections.size();

	connections.remove(connection);

	if (currentSize - 1 == connections.size())
		success = true;

	return success;
}

void
Node::destroyBlockChainModel(void)
{
	if (myBlockChainModel != nullptr) 
	{
		delete myBlockChainModel;
		myBlockChainModel = nullptr;
	}
}

Model_Blockchain* Node::getBlockChainModel(void)
{
	return myBlockChainModel;
}

void
Node::ping(void)
{
	notifyObservers();
	if (myBlockChainModel != nullptr)
		myBlockChainModel->ping();
}
