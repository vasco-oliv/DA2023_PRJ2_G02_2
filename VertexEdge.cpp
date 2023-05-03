#include "VertexEdge.h"

// **VERTEX**

Vertex::Vertex(unsigned int id) : id(id) {}

bool Vertex::addEdge(Vertex *dest, double weight) {
    for(auto &edge : adj){
        if(edge->getDest() == dest){
            return false;
        }
    }
    adj.push_back(std::make_unique<Edge>(this, dest, weight));
    return true;
}

bool Vertex::removeEdge(Vertex *dest) {
    for(auto it = adj.begin(); it != adj.end(); it++){
        if((*it)->getDest() == dest){
            adj.erase(it);
            return true;
        }
    }
    return false;
}

void Vertex::setVisited(bool visited) {
    this->visited=visited;
}

void Vertex::setDist(double dist) {
    this->dist=dist;
}


unsigned int Vertex::getId() const {
    return id;
}

bool Vertex::isVisited() const {
    return visited;
}

double Vertex::getDist() const {
    return dist;
}

const std::vector<std::unique_ptr<Edge>>& Vertex::getAdj() const {
    return adj;
}

// **EDGE**

Edge::Edge(Vertex *orig, Vertex *dest, double weight) {
    this->orig=orig;
    this->dest=dest;
    this->weight=weight;
}

Vertex *Edge::getOrig() const {
    return orig;
}

Vertex *Edge::getDest() const {
    return dest;
}

double Edge::getWeight() const {
    return weight;
}
