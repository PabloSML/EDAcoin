#pragma once
#include <string>
#include <list>
using namespace std;

class Node {
public:
	Node() { nodeType = string(""); }
	Node(string nodeType) { this->nodeType = nodeType; }
	~Node(){}

	string getNodeType() const { return nodeType; }
	void setNodeType(string nodeType) { this->nodeType = nodeType; }

	void attachConnection(Node* connection) { connections.push_back(connection); }
	void dettachConnection(Node* connection)
	{
		bool done = false;
		list<Node*>::iterator itr = connections.begin();
		int size = connections.size();
		for (int i = 0; i < size && !done; i++, itr++)
		{
			if (*itr == connection)
			{
				connections.erase(itr);
				done = true;
			}
		}
	}

protected:
	string nodeType;
	list<Node*> connections;
};
