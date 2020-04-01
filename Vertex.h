#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

class Vertex;

// streamable
#include <iostream>
#include <sstream>

// memory
#include <memory>

// stl containers
#include <vector>
#include <queue>

//other types
#include "Edge.h"

class Vertex {
public:
	int index;
	int distance;
	std::vector<Edge*> outbound_edges;
	std::vector<Edge*> inbound_edges;

	bool is_admissible() const;
};

#endif // VERTEX_H_INCLUDED