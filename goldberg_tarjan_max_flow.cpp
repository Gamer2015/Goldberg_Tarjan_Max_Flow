#include "goldberg_tarjan_max_flow.h"

void run(Graph& g) {
	// initialize flow
	for(auto& edge : g.edges) {
		if(edge.start == g.source) {
			edge.flow = edge.capacity;
		} else {
			edge.flow = 0;
		}
	}

	// initialize distances
	for(auto& vertex : g.vertices) {
		int distance = 0;
		if(vertex.index == g.source) {
			distance = g.nvertices;
		}
		if(vertex.index == g.target) {
			distance = 0;
		}
		vertex.distance = distance;
	}

	// initialize active vertices
	for(auto& vertex : g.vertices) {
		if(g.excess(vertex.index) > 0) {
			g.active_vertices.push(&vertex);
		}
	}

	while(g.active_vertices.size() > 0) {
		Vertex& vertex = *(g.active_vertices.front());
		if(vertex.distance < g.nvertices) {
			push_or_relabel(g, vertex);
		}
	}
}

void push(Graph& g, Vertex& v) {

}

void relabel(Graph& g, Vertex& v) {

}

void push_or_relabel(Graph& g, Vertex& v) {

}
