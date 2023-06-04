#include "Graph.h"
#include <cmath>

const std::vector<Vertex*> & Graph::getVertexSet() const{
    return vertexSet;
}

Vertex* Graph::findVertex(unsigned int id) const {
    for(auto it : vertexSet){
        if(it->getId() == id){
            return it;
        }
    }
    return nullptr;
}

void Graph::addVertex(Vertex* vertex) {
    vertexSet.push_back(vertex);
}

void Graph::addEdge(Vertex *v1, Vertex *v2, double weight) {
    v1->addEdge(v2, weight);
    v2->addEdge(v1, weight);
}

Edge *Graph::getEdge(Vertex *v1, Vertex *v2) {
    if(v1 == nullptr || v2 == nullptr) return nullptr;
    if(v1->getAdj().size() <= v2->getAdj().size()){
        for(Edge* e: v1->getAdj()){
            if(e->getDest() == v2){
                return e;
            }
        }
    }
    else{
        for(Edge* e: v2->getAdj()){
            if(e->getDest() == v1){
                return e;
            }
        }
    }
    return nullptr;
}

double Graph::getDist(unsigned int idOrig, unsigned int idDest) const {
    auto orig = findVertex(idOrig);
    auto dest = findVertex(idDest);
    if(orig == nullptr || dest == nullptr) return -1;

    for(const Edge* e: (*orig).getAdj()){
        if(e->getDest()->getId() == idDest){
            return e->getWeight();
        }
    }
    if(this->hasCoords){
        return calculateDist((*orig).getLatitude(), (*orig).getLongitude(), (*dest).getLatitude(), (*dest).getLongitude());
    }
    return -1;
}

double Graph::calculateDist(double lat1, double long1, double lat2, double long2) {
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (long2 - long1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371000;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

void Graph::clear() {
    vertexSet.clear();
}

void Graph::setFullyConnected(bool fullyConnected) {
    this->fullyConnected = fullyConnected;
}

void Graph::setHasCoords(bool hasCoords) {
    this->hasCoords = hasCoords;
}

bool Graph::usesCoords() const {
    return hasCoords;
}

bool Graph::isFullyConnected() const {
    return fullyConnected;
}
