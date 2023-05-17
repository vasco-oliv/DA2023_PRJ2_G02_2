
#ifndef DA2023_PRJ2_G02_2_VERTEXEDGE_H
#define DA2023_PRJ2_G02_2_VERTEXEDGE_H

#include <memory>
#include <vector>

class Edge;

class Vertex {
private:
    unsigned int id;
    std::vector<std::shared_ptr<Edge>> adj;
    bool visited = false;
    double dist = 0;
    double latitude;
    double longitude;

public:
    explicit Vertex(unsigned int id);
    Vertex(unsigned int id, double latitude, double longitude);
    bool addEdge(Vertex *dest, double weight);
    bool removeEdge(Vertex *dest);
    void setVisited(bool visited);
    void setDist(double dist);
    unsigned int getId() const;
    bool isVisited() const;
    double getDist() const;
    const std::vector<std::shared_ptr<Edge>>& getAdj() const;
};

class Edge{
private:
    Vertex *orig;
    Vertex *dest;
    double weight;

public:
    Edge(Vertex *orig, Vertex *dest, double weight);
    Vertex *getOrig() const;
    Vertex *getDest() const;
    double getWeight() const;
};

struct EdgeComparator {
    bool operator()(const std::shared_ptr<Edge> &e1, const std::shared_ptr<Edge> &e2) const {
        if(e1->getWeight() == e2->getWeight()) return e1->getDest()->getId() > e2->getDest()->getId();
        return e1->getWeight() > e2->getWeight();
    }
};

#endif //DA2023_PRJ2_G02_2_VERTEXEDGE_H
