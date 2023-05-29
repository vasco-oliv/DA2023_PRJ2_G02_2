#ifndef DA2023_PRJ2_G02_2_GRAPH_H
#define DA2023_PRJ2_G02_2_GRAPH_H

#include <vector>
#include <memory>
#include "VertexEdge.h"


class Graph {
private:
    std::vector<std::shared_ptr<Vertex>> vertexSet;

public:
    const std::vector<std::shared_ptr<Vertex>>& getVertexSet() const;
    std::vector<std::shared_ptr<Vertex>>::const_iterator findVertex(unsigned int id) const;
    bool addVertex(unsigned int id);
    bool addVertex(unsigned int id, double latitude, double longitude);
    bool addVertex(const std::shared_ptr<Vertex>& vertex);
    bool removeVertex(unsigned int id);
    bool addEdge(unsigned int idOrig, unsigned int idDest, double weight);
    double getDist(unsigned int idOrig, unsigned int idDest) const;
    double calculateDist(double lat1, double long1, double lat2, double long2) const;
};


#endif //DA2023_PRJ2_G02_2_GRAPH_H
