#include "Graph.h"

Graph Graph::residual() {
    Graph g;
    g.nvertices = this->nvertices;

    for(auto& edge : this->edges) {
        if( edge.flow < edge.capacity ) {
            g.edges.push_back(Edge(edge.start, edge.end, edge.weight, edge.capacity - edge.flow));
        } 
        if( edge.flow > 0 ) {
            g.edges.push_back(Edge(edge.start, edge.end, edge.weight, edge.flow));
        } 
    }
    g.nedges = g.edges.size();
    g.source = this->source;
    g.target = this->target;

    return g;
}

int Graph::excess(int n) const {
    const Vertex& v = this->vertices[n];
    int total = 0;
    for(auto edge : v.outbound_edges) {
        total -= edge->flow;
    }
    for(auto edge : v.inbound_edges) {
        total += edge->flow;
    }
    return total;
}

bool Graph::edge_admissible(int start, int end) const {
    return this->vertices[start].distance == this->vertices[end].distance + 1;
}

std::istream& operator>>( std::istream& input, Graph& graph ) { 
    // dummy string for getline
    std::string line = "";

    // first line, base data
    std::getline(input, line);
    { 
        std::stringstream linestream(line);

        linestream >> graph.nvertices >> graph.nedges >> graph.source >> graph.target;
    }

    graph.vertices = std::vector<Vertex>(graph.nvertices + 1);
    int i = 0; // the 0th vertex is just a dummy
    for(auto vertex : graph.vertices) {
        vertex.index = i;
        ++i;
    }

    // other lines, vertices
    std::getline(input, line);
    while (input.fail() == false && line != "end") {
        std::stringstream linestream(line);

        graph.edges.push_back(Edge(linestream));
        Edge& inserted_edge = graph.edges.back();
        graph.vertices[inserted_edge.start].outbound_edges.push_back(&inserted_edge);
        graph.vertices[inserted_edge.end].inbound_edges.push_back(&inserted_edge);

        // std::cout << "edges: " << graph.edges.size() << "; last: " <<  graph.edges.back() << std::endl;
        std::getline(input, line);
    }
    return input;
}
