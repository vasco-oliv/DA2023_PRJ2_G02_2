#include "Graph.h"
#include <cmath>

const std::vector<std::shared_ptr<Vertex>> &Graph::getVertexSet() const {
    return vertexSet;
}

std::vector<std::shared_ptr<Vertex>>::const_iterator Graph::findVertex(unsigned int id) const {
    for(auto it= vertexSet.begin(); it != vertexSet.end(); it++){
        if((*it)->getId() == id){
            return it;
        }
    }
    return vertexSet.end();
}

[[maybe_unused]] bool Graph::addVertex(unsigned int id) {
    if(findVertex(id) != vertexSet.end()) return false;

    vertexSet.push_back(std::make_shared<Vertex>(id));
    return true;
}

bool Graph::addVertex(unsigned int id, double latitude, double longitude) {
    if(findVertex(id) != vertexSet.end()) return false;

    vertexSet.push_back(std::make_shared<Vertex>(id, latitude, longitude));
    return true;
}

bool Graph::addVertex(const std::shared_ptr<Vertex>& vertex) {
    if(findVertex(vertex->getId()) != vertexSet.end()) return false;

    vertexSet.push_back(vertex);
    return true;
}

bool Graph::removeVertex(unsigned int id) {
    auto v= findVertex(id);
    if(v == vertexSet.end()) return false;

    vertexSet.erase(v);
    return true;
}

bool Graph::addEdge(unsigned int idOrig, unsigned int idDest, double weight) {
    auto orig = findVertex(idOrig);
    auto dest = findVertex(idDest);

    if(orig == vertexSet.end() || dest == vertexSet.end()) return false;

    return ((*orig)->addEdge((*dest), weight) && (*dest)->addEdge((*orig), weight));
}

double Graph::getDist(unsigned int idOrig, unsigned int idDest) const {
    auto orig = findVertex(idOrig);
    auto dest = findVertex(idDest);
    if(orig == vertexSet.end() || dest == vertexSet.end()) return -1;

    for(const std::shared_ptr<Edge>& e:orig->get()->getAdj()){
        if(e->getDest()->getId() == idDest){
            return e->getWeight();
        }
    }
    if(this->hasCoords){
        return calculateDist((*orig)->getLatitude(), (*orig)->getLongitude(), (*dest)->getLatitude(), (*dest)->getLongitude());
    }
    return -1;
}

double Graph::getDist(Vertex *v1, Vertex *v2) const {
    if(v1 == nullptr || v2 == nullptr) return -1;

    for(const std::shared_ptr<Edge>& e:v1->getAdj()){
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
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

void Graph::clear() {
    for (auto &v : vertexSet) {
        v->clear();
        v.reset();
    }
    vertexSet.clear();
}

