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
private:
	int _excess;

public:
	int index;
	unsigned int distance;

	std::vector<Edge*> outbound_edges;
	std::vector<Edge*> inbound_edges;

	bool active() const;
	int excess() const;
	int excess(int difference);
	int excess_recalculate();

	// user has to make sure not to expose the input-stream
	friend std::ostream &operator<<( std::ostream &ostream, const Vertex &vertex);
};

#endif // VERTEX_H_INCLUDED