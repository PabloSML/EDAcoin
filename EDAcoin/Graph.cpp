#include "Graph.h"

Graph::Graph(int vertexCount) : n(vertexCount), e(0)
{
	mark = new int[n];
	resetMarks();
	matrix = new int*[n];
	for (int i = 0; i < n; i++)
		matrix[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = 0;
}

Graph::~Graph()
{
	for (int i = 0; i < n; i++)
		delete[] matrix[i];
	delete[] matrix;
	delete[] mark;
}

int Graph::getN(void) const { return n; }
int Graph::getE(void) const { return e; }

int
Graph::getFirst(int v)
{
	for (int i = 0; i < n; i++)
		if (matrix[v][i] != 0)
			return i;
	return n;
}

int
Graph::getNext(int v, int v2)
{
	for (int i = v2 + 1; i < n; i++)
		if (matrix[v][i] != 0)
			return i;
	return n;
}

void
Graph::setEdge(int v, int v2)
{
	if (matrix[v][v2] == 0)
		e++;
	matrix[v][v2] = 1;
	matrix[v2][v] = 1;
}

void
Graph::removeEdge(int v, int v2)
{
	if (matrix[v][v2] != 0)
		e--;
	matrix[v][v2] = 0;
	matrix[v2][v] = 0;
}

bool
Graph::isEdge(int v, int v2)
{
	return matrix[v][v2] != 0;
}

int
Graph::countEdges(int v)
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (matrix[v][i] != 0)
			count++;
	}
	return count;
}

int
Graph::getMark(int v)
{
	return mark[v];
}

void
Graph::setMark(int v, int value)
{
	mark[v] = value;
}

void
Graph::resetMarks(void)
{
	for (int i = 0; i < n; i++)
		setMark(i, UNVISITED);
}

int
Graph::BFSCount(int v)
{
	int count = 0;
	queue<int> queue;
	resetMarks();

	queue.push(v);
	setMark(v, VISITED);

	while (!queue.empty())
	{
		int tempV = queue.front();
		queue.pop();

		count++;

		for (int v2 = getFirst(tempV); v2 < n; v2 = getNext(tempV, v2))
		{
			if (getMark(v2) == UNVISITED)
			{
				setMark(v2, VISITED);
				queue.push(v2);
			}
		}
	}

	return count;
}