#include "Graph.h"
#include <cmath>

const std::vector<Vertex*> & Graph::getVertexSet() const{
    return vertexSet;
}

Vertex* Graph::findVertex(unsigned int id) const {
    for(auto it= vertexSet.begin(); it != vertexSet.end(); it++){
        if((*it)->getId() == id){
            return *it;
        }
    }
    return nullptr;
}

bool Graph::addVertex(unsigned int id) {
    if(findVertex(id) != nullptr) return false;
    vertexSet.push_back(new Vertex(id));
    return true;
}

bool Graph::addVertex(unsigned int id, double latitude, double longitude) {
    if(findVertex(id) != nullptr) return false;
    vertexSet.push_back(new Vertex(id, latitude, longitude));
    return true;
}

void Graph::addVertex(Vertex* vertex) {
    vertexSet.push_back(vertex);
}

/*
bool Graph::removeVertex(unsigned int id) {
    auto v= findVertex(id);
    if(v == vertexSet.end()) return false;

    vertexSet.erase(v);
    return true;
} */

void Graph::addEdge(unsigned int idOrig, unsigned int idDest, double weight) {
    auto orig = findVertex(idOrig);
    auto dest = findVertex(idDest);

    if(orig == nullptr || dest == nullptr) return;

    orig->addEdge(dest, weight);
    dest->addEdge(orig, weight);
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

double Graph::getDist(Vertex *v1, Vertex *v2) const {
    if(v1 == nullptr || v2 == nullptr) return -1;

    for(const Edge* e:v1->getAdj()){
        if(e->getDest()->getId() == v2->getId()){
            return e->getWeight();
        }
    }
    if(this->hasCoords){
        return calculateDist(v1->getLatitude(), v1->getLongitude(), v2->getLatitude(), v2->getLongitude());
    }
    return -1;
}

double Graph::calculateDist(double lat1, double long1, double lat2, double long2) {
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (long2 - long1) *
                  M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371000;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

void Graph::clear() {
    for (auto &v : vertexSet) {
        v->clear();
        delete v;
    }
    vertexSet.clear();
}

Edge *Graph::getEdge(Vertex *v1, Vertex *v2) const {
    for(Edge* e: v1->getAdj()){
        if(e->getDest() == v2){
            return e;
        }
    }
    return nullptr;
}

void Graph::setFullyConnected(bool isFullyConnected) {
    this->isFullyConnected = isFullyConnected;
}

void Graph::setHasCoords(bool hasCoords) {
    this->hasCoords = hasCoords;
}

bool Graph::usesCoords() const {
    return hasCoords;
}

bool Graph::fullyConnected() const {
    return isFullyConnected;
}
