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
Node::push_message(blockchain_message& message)
{
	(this->buffer_messages).push_back(message);
}

void
Node::createBlockChainModel(void)
{
	if (myBlockChainModel == nullptr)
	{
		myBlockChainModel = new Model_Blockchain(this);
		View_Blockchain* tempView = new View_Blockchain(WIDTH_DEFAULT, HEIGHT_DEFAULT);
		myBlockChainModel->attach(tempView);
	}
}

void
Node::destroyBlockChainModel(void)
{
	if (myBlockChainModel != nullptr) 
	{
		delete myBlockChainModel;
	}
}

/*
Controller_BlockChain*
Node::createBlockChainController(void)
{
	return new Controller_BlockChain(myBlockChainModel);
}

void
Node::destroyBlockChainController(Controller_BlockChain* target)
{
	delete target;
}
*/