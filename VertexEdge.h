
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
    int dist = 0;
    double latitude;
    double longitude;
    unsigned int previous;

public:
    explicit Vertex(unsigned int id);
    Vertex(unsigned int id, double latitude, double longitude);
    bool addEdge(std::shared_ptr<Vertex> dest, double weight);
    bool removeEdge(std::shared_ptr<Vertex> dest);
    void setVisited(bool visited);
    void setDist(int dist);
    unsigned int getId() const;
    bool isVisited() const;
    int getDist() const;
    double getLatitude() const;
    double getLongitude() const;
    void setPrevious(unsigned int previous);
    unsigned int getPrevious() const;
    const std::vector<std::shared_ptr<Edge>>& getAdj() const;
};

class Edge{
private:
    std::shared_ptr<Vertex> orig;
    std::shared_ptr<Vertex> dest;
    double weight;

public:
    Edge(std::shared_ptr<Vertex>orig, std::shared_ptr<Vertex>dest, double weight);
    std::shared_ptr<Vertex> getOrig() const;
    std::shared_ptr<Vertex> getDest() const;
    double getWeight() const;
};

struct EdgeComparator {
    bool operator()(const std::shared_ptr<Edge> &e1, const std::shared_ptr<Edge> &e2) const {
        if(e1->getWeight() == e2->getWeight()) return e1->getDest()->getId() > e2->getDest()->getId();
        return e1->getWeight() > e2->getWeight();
    }
};

#endif
