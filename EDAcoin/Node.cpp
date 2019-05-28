#include "Node.h"

void
Node::dettachConnection(Node* connection)
{
	bool done = false;
	list<Node*>::iterator itr = connections.begin();
	int size = (int) connections.size();
	for (int i = 0; i < size && !done; i++, itr++)
	{
		if (*itr == connection)
		{
			connections.erase(itr);
			done = true;
		}
	}
}