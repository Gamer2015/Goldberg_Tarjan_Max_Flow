#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

class Graph;

// streamable
#include <iostream>
#include <sstream>

// stl containers
#include <vector>
#include <map>

//other types
#include "Edge.h"
#include "Vertex.h"

class Graph {
public:
	int nvertices, nedges, source, target;
	std::vector<Vertex> vertices;
	std::vector<Edge> edges;

	std::map<int, int> dijkstra(int start, bool use_arcs_backwards=false) const;

	bool edge_admissible(int start, int end) const;

	Graph residual();
	friend std::istream &operator>>( std::istream &input, Graph &graph );
	friend std::ostream &operator<<( std::ostream &ostream, const Graph &graph);
};

#endif // GRAPH_H_INCLUDED