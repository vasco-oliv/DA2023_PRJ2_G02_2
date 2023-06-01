
#ifndef DA2023_PRJ2_G02_2_VERTEXEDGE_H
#define DA2023_PRJ2_G02_2_VERTEXEDGE_H

#include <memory>
#include <vector>

class Edge;

class Vertex {
private:
    unsigned int id;
    std::vector<Edge*> adj;
    bool visited = false;
    int dist = 0;
    double latitude;
    double longitude;
    unsigned int previous;

public:
    std::vector<Vertex*> sons;

    /// @brief Creates a vertex with the given id.
    /// @param id The id of the vertex to create
    /// @note Time Complexity: O(1)
    explicit Vertex(unsigned int id);

    /// @brief Creates a vertex with the given id, latitude and longitude.
    /// @param id The id of the vertex to create
    /// @param latitude The latitude of the vertex to create
    /// @param longitude The longitude of the vertex to create
    /// @note Time Complexity: O(1)
    Vertex(unsigned int id, double latitude, double longitude);

    /// @brief Adds an edge from this vertex to the specified destination vertex with the given weight.
    /// @param dest The destination vertex of the edge to add
    /// @param weight The weight of the edge to add
    /// @return True if the edge was added, false otherwise
    /// @note Time Complexity: O(E), where E is the number of edges in the graph
    bool addEdge(Vertex*& dest, double weight);

    /// @brief Removes the edge from this vertex to the specified destination vertex.
    /// @param dest The destination vertex of the edge to remove
    /// @return True if the edge was removed, false otherwise
    /// @note Time Complexity: O(E), where E is the number of edges in the graph
    bool removeEdge(Vertex*& dest);

    /// @brief Gets the id of this vertex.
    /// @return The id of this vertex
    /// @note Time Complexity: O(1)
    unsigned int getId() const;

    /// @brief Gets the value of the visited flag of this vertex.
    /// @return The value of the visited flag of this vertex
    /// @note Time Complexity: O(1)
    bool isVisited() const;

    /// @brief Sets the visited flag of this vertex.
    /// @param visited The value to set the visited flag to
    /// @note Time Complexity: O(1)
    void setVisited(bool visited);

    /// @brief Gets the distance of this vertex.
    /// @return The distance of this vertex
    /// @note Time Complexity: O(1)
    int getDist() const;
    
    /// @brief Sets the distance of this vertex.
    /// @param dist The value to set the distance to
    /// @note Time Complexity: O(1)
    void setDist(int dist);

    /// @brief Gets the latitude of this vertex.
    /// @return The latitude of this vertex
    /// @note Time Complexity: O(1)
    double getLatitude() const;

    /// @brief Gets the longitude of this vertex.
    /// @return The longitude of this vertex
    /// @note Time Complexity: O(1)
    double getLongitude() const;

    /// @brief Sets the previous vertex of this vertex to the specified id.
    /// @param previous The id of the updated previous vertex
    /// @note Time Complexity: O(1)
    void setPrevious(unsigned int previous);

    /// @brief Gets the id of the previous vertex of this vertex.
    /// @return The id of the previous vertex of this vertex
    /// @note Time Complexity: O(1)
    unsigned int getPrevious() const;

    /// @brief Gets the adjacent edges of the vertex.
    /// @return A vector with the adjacent edges of the vertex
    /// @note Time Complexity: O(1)
    const std::vector<Edge*>& getAdj() const;

    /// @brief Deletes all the adjacent edges of the vertex.
    /// @note Time Complexity: O(1)
    void clear();
};

class Edge{
private:
    Vertex* orig;
    Vertex* dest;
    double weight;

public:

    /// @brief Creates an edge between the given origin and destination vertices with the specified weight.
    /// @param orig The origin vertex of the edge to create
    /// @param dest The destination vertex of the edge to create
    /// @param weight The weight of the edge to create
    /// @note Time Complexity: O(1)
    Edge(Vertex* orig, Vertex* dest, double weight);

    /// @brief Gets the origin vertex of this edge.
    /// @return The origin vertex of this edge
    /// @note Time Complexity: O(1)
    Vertex* getOrig() const;

    /// @brief Gets the destination vertex of this edge.
    /// @return The destination vertex of this edge
    /// @note Time Complexity: O(1)
    Vertex* getDest() const;

    /// @brief Gets the weight of this edge.
    /// @return The weight of this edge
    /// @note Time Complexity: O(1)
    double getWeight() const;
};

struct EdgeComparator {

    /// @brief Overloaded function call operator that compares two edges.
    /// @param e1 The first edge to compare
    /// @param e2 The second edge to compare
    /// @return True if the first edge is less than the second, false otherwise
    /// @note Time Complexity: O(1)
    bool operator()(Edge *e1, Edge *e2) const {
        if(e1->getWeight() == e2->getWeight()) return e1->getDest()->getId() > e2->getDest()->getId();
        return e1->getWeight() > e2->getWeight();
    }
};

#endif
