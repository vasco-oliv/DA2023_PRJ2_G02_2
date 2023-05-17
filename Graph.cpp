#include "Graph.h"

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

bool Graph::addVertex(unsigned int id) {
    if(findVertex(id) != vertexSet.end()){
        return false;
    }
    vertexSet.push_back(std::make_shared<Vertex>(id));
    return true;
}

bool Graph::removeVertex(unsigned int id) {
    auto v= findVertex(id);
    if(v == vertexSet.end()){
        return false;
    }
    vertexSet.erase(v);
    return true;
}

bool Graph::addEdge(unsigned int idOrig, unsigned int idDest, double weight) {
    auto orig = findVertex(idOrig);
    auto dest = findVertex(idDest);
    if(orig == vertexSet.end() || dest == vertexSet.end()){
        return false;
    }
    return ( (*orig)->addEdge((*dest), weight) && (*dest)->addEdge((*orig), weight) );

}

bool Graph::addVertex(unsigned int id, double latitude, double longitude) {
    if(findVertex(id) != vertexSet.end()){
        return false;
    }
    vertexSet.push_back(std::make_shared<Vertex>(id, latitude, longitude));
    return true;
}
