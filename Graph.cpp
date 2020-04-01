#include "Graph.h"

/*
Graph Graph::residual() {
    Graph g;
    g.nvertices = this->nvertices;

    for(auto &edge : this->edges) {
        if( edge.is_residual_forward_arc(edge) ) {
            g.edges.push_back(Edge(edge.start, edge.end, edge.weight, edge.capacity - edge.flow));
        } 
        if( edge.is_residual_backward_arc(edge) ) {
            g.edges.push_back(Edge(edge.end, edge.start, edge.weight, edge.flow));
        } 
    }
    g.nedges = g.edges.size();
    g.source = this->source;
    g.target = this->target;

    return g;
}*/


std::istream &operator>>( std::istream &input, Graph &graph ) { 
    // dummy string for getline
    std::string line = "";

    // first line, base data
    { 
        std::getline(input, line);
        std::stringstream linestream(line);
        linestream >> graph.nvertices >> graph.nedges >> graph.source >> graph.target;
    }
    // initialize vertices
    { 
        graph.vertices = std::vector<Vertex>(graph.nvertices + 1);
        int i = 0; // the 0th vertex is just a dummy
        for(auto &vertex : graph.vertices) {
            vertex.index = i;
            ++i;
        }
    }

    // other lines, vertices
    std::getline(input, line);
    while (input.fail() == false && line != "end") {
        std::stringstream linestream(line);
        graph.edges.emplace_back(graph, linestream);
        std::getline(input, line);
    }

    for(auto &edge : graph.edges) {
        edge.start_vertex().outbound_edges.push_back(&edge);
        edge.end_vertex().inbound_edges.push_back(&edge);
    }

    return input;
}

std::ostream &operator<<( std::ostream &ostream, const Graph &g ) { 
    std::cout << "Vertices: " << std::endl;
    for(const auto &vertex : g.vertices) {
        std::cout << vertex << std::endl;
    }
    std::cout << std::endl << "Edges: " << std::endl;
    for(const auto &edge : g.edges) {
        std::cout << edge << std::endl;
    }

    std::cout << "Outbound Edges: " << std::endl;
    for(const auto &vertex : g.vertices) {
        std::cout << vertex << std::endl;
        for(auto edge : vertex.outbound_edges) {
            std::cout << " - " << *edge << std::endl;
        }
    }
    std::cout << "Inbound Edges: " << std::endl;
    for(const auto &vertex : g.vertices) {
        std::cout << vertex << std::endl;
        for(auto edge : vertex.inbound_edges) {
            std::cout << " - " << *edge << std::endl;
        }
    }
    return ostream;            
}