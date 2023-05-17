#include "VertexEdge.h"

#include <utility>

// **VERTEX**

Vertex::Vertex(unsigned int id) : id(id) {}

Vertex::Vertex(unsigned int id, double latitude, double longitude) {
    this->id=id;
    this->latitude=latitude;
    this->longitude=longitude;

}
bool Vertex::addEdge(std::shared_ptr<Vertex> dest, double weight) {
    for(auto &edge : adj){
        if(edge->getDest() == dest){
            return false;
        }
    }
    adj.push_back(std::make_shared<Edge>(std::make_shared<Vertex>(this -> id, this -> longitude, this -> latitude), dest, weight));
    return true;
}

bool Vertex::removeEdge(std::shared_ptr<Vertex> dest) {
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

const std::vector<std::shared_ptr<Edge>>& Vertex::getAdj() const {
    return adj;
}


// **EDGE**

Edge::Edge(std::shared_ptr<Vertex>orig, std::shared_ptr<Vertex>dest, double weight) {
    this->orig=std::move(orig);
    this->dest=std::move(dest);
    this->weight=weight;
}

std::shared_ptr<Vertex>Edge::getOrig() const {
    return orig;
}

std::shared_ptr<Vertex>Edge::getDest() const {
    return dest;
}

double Edge::getWeight() const {
    return weight;
}


