#include "Vertex.h"

bool Vertex::active() const {
    return this->excess() > 0;
}
int Vertex::excess() const {
    return this->_excess;
}
int Vertex::excess(int incoming_amount) {
    this->_excess += incoming_amount;
    return this->excess();
}
int Vertex::excess_recalculate() {
    int total = 0;
    for(auto edge : this->outbound_edges) {
        total += edge->flow();
    }
    for(auto edge : this->inbound_edges) {
        total -= edge->flow();
    }
    this->_excess = total;
    return this->excess();
}

std::ostream &operator<<( std::ostream &ostream, const Vertex &vertex ) { 
    ostream << "index: " << vertex.index << "; excess: " << vertex.excess() << "; distance: " << vertex.distance << "; outbound: " << vertex.outbound_edges.size() << "; inbound: " << vertex.inbound_edges.size() << ";";
    return ostream;            
}