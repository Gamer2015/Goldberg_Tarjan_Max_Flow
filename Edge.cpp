#include "Edge.h"

Edge::Edge(std::istream& input) {
	input >> *this;
}
Edge::Edge(int start, int end, int weight, int capacity, int flow) {
	this->start = start;
	this->end = end;
	this->weight = weight;
	this->capacity = capacity;
	this->flow = flow;
}

std::istream& operator>>( std::istream& input, Edge& edge ) { 
	input >> edge.start >> edge.end >> edge.weight >> edge.capacity >> edge.flow;
	return input;            
}
std::ostream& operator<<( std::ostream& ostream, const Edge& edge ) { 
	ostream << "start: " << edge.start << "; end: " << edge.end << "; weight: " << edge.weight << "; capacity: " << edge.capacity << "; flow: " << edge.flow << ";";
	return ostream;            
}