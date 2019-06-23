#pragma once
#include <queue>
#include "Node.h"
using namespace std;
#define UNVISITED 0
#define VISITED 1

class Graph
{
public:
	Graph(int n);
	~Graph();

	int getN() const;
	int getE() const;
	
	int getFirst(int v);
	int getNext(int v, int v2);

	void setEdge(int v, int v2);
	void removeEdge(int v, int v2);
	bool isEdge(int v, int v2);
	int countEdges(int v);

	int getMark(int v);
	void setMark(int v, int value);
	void resetMarks();

	int BFSCount(int v);

private:
	int n, e;
	int** matrix;
	int* mark;
};