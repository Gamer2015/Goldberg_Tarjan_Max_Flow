#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

class Graph;

// streamable
#include <iostream>
#include <sstream>

// stl containers
#include <vector>
#include <queue>

//other types
#include "Edge.h"
#include "Vertex.h"

class Graph {
public:
	int nvertices, nedges, source, target;
	std::vector<Vertex> vertices;
	std::vector<Edge> edges;

	std::queue<Vertex*> active_vertices;
	std::queue<int> highest_label;
	std::queue<int> highest_excess;

	bool edge_admissible(int start, int end) const;

	Graph residual();
	int excess(int n) const;
	friend std::istream &operator>>( std::istream &input, Graph &D );
};

#endif // GRAPH_H_INCLUDED