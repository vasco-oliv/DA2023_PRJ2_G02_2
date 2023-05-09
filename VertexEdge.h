
#ifndef DA2023_PRJ2_G02_2_VERTEXEDGE_H
#define DA2023_PRJ2_G02_2_VERTEXEDGE_H

#include <vector>
#include <memory>

class Edge;

class Vertex {
private:
    unsigned int id;
    std::vector<std::unique_ptr<Edge>> adj;
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
    const std::vector<std::unique_ptr<Edge>>& getAdj() const;
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


#endif //DA2023_PRJ2_G02_2_VERTEXEDGE_H
