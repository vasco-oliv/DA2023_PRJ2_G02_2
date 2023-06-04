#include "VertexEdge.h"

// **VERTEX**

Vertex::Vertex(unsigned int id) : id(id) {}

Vertex::Vertex(unsigned int id, double latitude, double longitude) {
    this->id=id;
    this->latitude=latitude;
    this->longitude=longitude;
}

bool Vertex::addEdge(Vertex* dest, double weight) {
    adj.push_back(new Edge(this, dest, weight));
    return true;
}

unsigned int Vertex::getId() const {
    return id;
}

bool Vertex::isVisited() const {
    return visited;
}

void Vertex::setVisited(bool visited) {
    this->visited=visited;
}

double Vertex::getLatitude() const {
    return latitude;
}

double Vertex::getLongitude() const {
    return longitude;
}

const std::vector<Edge*>& Vertex::getAdj() const {
    return adj;
}

void Vertex::clear() {
    for (auto edge : adj) {
        edge -> clear();
        delete edge;
    }
    adj.clear();
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

double Vertex::getDist() const {
    return dist;
}

void Vertex::setPrevious(Vertex *previous) {
    this->previous = previous;

}

Vertex *Vertex::getPrevious() const {
    return previous;
}

void Vertex::clearMSTadj() {
    for (auto edge : MSTadj) {
        edge -> clear();
        delete edge;
    }
    MSTadj.clear();
}

// **EDGE**

Edge::Edge(Vertex* orig, Vertex* dest, double weight) {
    this->orig=orig;
    this->dest=dest;
    this->weight=weight;
}

Vertex* Edge::getOrig() const {
    return orig;
}

Vertex* Edge::getDest() const {
    return dest;
}

double Edge::getWeight() const {
    return weight;
}

void Edge::clear() {
    orig = nullptr;
    dest = nullptr;
}
