#include "Graph.h"

// container 
#include <set>

using namespace std;

Graph Graph::residual(){
    Graph graph;

    graph.nvertices = this->nvertices;
    graph.source = this->source;
    graph.target = this->target;
    // initialize vertices
    { 
        graph.vertices = vector<Vertex>(graph.nvertices + 1);
        int i = 0; // the 0th vertex is just a dummy
        for(auto &vertex : graph.vertices) {
            vertex.index = i;
            ++i;
        }
    }

    for(auto &edge : this->edges) {
        if( edge.is_residual_forward_arc() ) {
            graph.edges.emplace_back(graph, edge.start, edge.end, edge.residual_forward_capacity());
        } 
        if( edge.is_residual_backward_arc() ) {
            graph.edges.emplace_back(graph, edge.end, edge.start, edge.residual_backward_capacity());
        } 
    }

    graph.nedges = graph.edges.size();

    // connect to edges
    for(auto &edge : graph.edges) {
        edge.start_vertex().outbound_edges.push_back(&edge);
        edge.end_vertex().inbound_edges.push_back(&edge);
    }

    return graph;
}

map<int, int> Graph::dijkstra(int start, bool use_arcs_backwards) const {
    map<int, int> parents;
    map<int, int> distances;
    distances[start] = 0;

    set<int> scanned;
    set<int> unscanned;
    for(const auto& vertex : this->vertices) {
        unscanned.insert(vertex.index);
    }

    while(unscanned.size() > 0) {
        int scan_index = *std::min_element(unscanned.begin(), unscanned.end());
        unscanned.erase(scan_index);

        const Vertex& current = this->vertices[scan_index];
        const std::vector<Edge*>& edges = (use_arcs_backwards ? current.inbound_edges : current.outbound_edges );
        for(auto edge : edges) {
            int to_index = edge->end_vertex().index;
            if(unscanned.find(to_index) != unscanned.end()) {
                int distance = distances[scan_index] + edge->weight;
                if(distances.find(to_index) != distances.end()) {
                    if(distance < distances[to_index]) {
                        distances[to_index] = distance;
                        parents[to_index] = scan_index;   
                    }
                }
            }
        }
    }
    return distances;
}


istream &operator>>( istream &input, Graph &graph ) { 
    // dummy string for getline
    string line = "";

    // first line, base data
    { 
        getline(input, line);
        stringstream linestream(line);
        linestream >> graph.nvertices >> graph.nedges >> graph.source >> graph.target;
    }
    // initialize vertices
    { 
        graph.vertices = vector<Vertex>(graph.nvertices + 1);
        int i = 0; // the 0th vertex is just a dummy
        for(auto &vertex : graph.vertices) {
            vertex.index = i;
            ++i;
        }
    }

    // other lines, vertices
    getline(input, line);
    while (input.fail() == false && line != "end") {
        stringstream linestream(line);
        graph.edges.emplace_back(graph, linestream);
        getline(input, line);
    }

    for(auto &edge : graph.edges) {
        edge.start_vertex().outbound_edges.push_back(&edge);
        edge.end_vertex().inbound_edges.push_back(&edge);
        edge.weight = 1;
    }

    map<int, int> distances = graph.dijkstra(graph.target, true);
    for(auto &vertex : graph.vertices) {
        if(distances.find(vertex.index) != distances.end()) {
            vertex.distance = distances[vertex.index];
        } else {
            vertex.distance = graph.nvertices;
        }
    }

    return input;
}

ostream &operator<<( ostream &ostream, const Graph &g ) { 
    cout << "Vertices: " << endl;
    for(const auto &vertex : g.vertices) {
        cout << vertex << endl;
    }
    cout << endl << "Edges: " << endl;
    for(const auto &edge : g.edges) {
        cout << edge << endl;
    }

    cout << "Outbound Edges: " << endl;
    for(const auto &vertex : g.vertices) {
        cout << vertex << endl;
        for(auto edge : vertex.outbound_edges) {
            cout << " - " << *edge << endl;
        }
    }
    cout << "Inbound Edges: " << endl;
    for(const auto &vertex : g.vertices) {
        cout << vertex << endl;
        for(auto edge : vertex.inbound_edges) {
            cout << " - " << *edge << endl;
        }
    }
    return ostream;            
}