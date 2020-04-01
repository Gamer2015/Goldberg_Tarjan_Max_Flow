#include "Edge.h"

using namespace std;

Edge::Edge(Graph &g, istream &input) 
: graph(g), start(0), end(0), capacity(0), _flow(0) {
	input >> *this;
}
Edge::Edge(Graph &g, int start, int end, int capacity, int flow)
: graph(g), start(start), end(end), capacity(capacity), _flow(0) {
	this->flow(flow);
}

Vertex &Edge::start_vertex() {
	return this->graph.vertices[start];
}
const Vertex &Edge::start_vertex() const {
	return this->graph.vertices[start];
}
Vertex &Edge::end_vertex() {
	return this->graph.vertices[end];
}
const Vertex &Edge::end_vertex() const {
	return this->graph.vertices[end];
}

int Edge::flow() const {
	return this->_flow;
}
int Edge::flow(int new_flow) {
	int outbound_difference = new_flow - this->flow();
	this->start_vertex().excess(-outbound_difference);
	this->end_vertex().excess(outbound_difference);
	this->_flow = new_flow;
	return this->flow();
}

bool Edge::is_residual_forward_arc() const {
	return this->flow() < this->capacity;
}
bool Edge::is_residual_backward_arc() const {
	return this->flow() > 0;
}
// assuming the arcs are in the residual graph
int Edge::residual_forward_capacity() const { 
	return this->capacity - this->flow();
}
int Edge::residual_backward_capacity() const {
	return this->flow();
}

// assuming the arcs are in the residual graph
bool Edge::is_residual_forward_admissible() const {
	return this->start_vertex().distance == this->end_vertex().distance + 1;
}
bool Edge::is_residual_backward_admissible() const {
	return this->end_vertex().distance == this->start_vertex().distance + 1;
}

istream &operator>>( istream &input, Edge &edge ) { 
	input >> edge.start >> edge.end >> edge.capacity;
	return input;            
}
ostream &operator<<( ostream &ostream, const Edge &edge ) { 
	ostream << edge.start << ", " << edge.end << ", " << edge.capacity << ", " << edge.flow();
	return ostream;            
}