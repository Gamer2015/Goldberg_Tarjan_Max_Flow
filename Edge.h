#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

class Edge;

// streamable
#include <iostream>

// other types
#include "Graph.h"
#include "Vertex.h"

class Edge {
private:
	int _flow;

public:
	Graph &graph;

	int start, end;
	int capacity;

	Edge(Graph &g, std::istream &istream);
	Edge(Graph &g, int start=0, int end=0, int capacity=0, int flow=0);

	Vertex &start_vertex();
	const Vertex &start_vertex() const;
	Vertex &end_vertex();
	const Vertex &end_vertex() const;

	int flow() const;
	int flow(int new_flow);

	bool is_residual_forward_arc() const;
	bool is_residual_backward_arc() const;

	bool is_residual_forward_admissible() const;
	bool is_residual_backward_admissible() const;
	
	int residual_forward_capacity() const;
	int residual_backward_capacity() const;

	// user has to make sure not to expose the input-stream
	friend std::istream &operator>>( std::istream  &input, Edge &edge );
	friend std::ostream &operator<<( std::ostream &ostream, const Edge &edge);
};

#endif // EDGE_H_INCLUDED