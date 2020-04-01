#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

// streamable
#include <iostream>

class Edge {
public:
	int start, end, weight;
	int capacity, flow;

	Edge(std::istream& istream);
	Edge(int start=0, int end=0, int weight=0, int capacity=0, int flow=0);

	// user has to make sure not to expose the input-stream
	friend std::istream& operator>>( std::istream  &input, Edge &edge );
	friend std::ostream& operator<<( std::ostream& ostream, const Edge& edge);
};

#endif // EDGE_H_INCLUDED