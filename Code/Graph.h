#ifndef DA2023_PRJ2_G02_2_GRAPH_H
#define DA2023_PRJ2_G02_2_GRAPH_H

#include <vector>
#include "VertexEdge.h"

class Graph {
private:
    std::vector<Vertex*> vertexSet;
    bool fullyConnected = false;
    bool hasCoords = false;
public:
    /// @brief Gets all the vertices in the graph.
    /// @return A vector with all the vertices in the graph
    const std::vector<Vertex *> & getVertexSet() const;

    /// @brief Finds a vertex in the graph, given its id.
    /// @param id The id of the vertex to find
    /// @return A point to the vertex if found, otherwise returns nullptr
    /// @note Time Complexity: O(V), where V is the number of vertices in the graph
    Vertex* findVertex(unsigned int id) const;

    /// @brief Adds a vertex to the graph.
    /// @param vertex The vertex to add
    /// @return True if the vertex was added, false otherwise
    /// @note Time Complexity: O(V), where V is the number of vertices in the graph
    void addVertex(Vertex* vertex);

    /// @brief Adds an edge to the graph, given two vertices and its weight.
    /// @param v1 The origin vertex of the edge to add
    /// @param v2 The destination vertex of the edge to add
    /// @param weight The weight of the edge to add
    /// @return True if the edge was added, false otherwise
    /// @note Time Complexity: O(V), where V is the number of vertices in the graph
    void addEdge(Vertex* v1, Vertex* v2, double weight);
    
    /// @brief Gets the distance between two vertices, given their ids.
    /// @param v1 Origin vertex
    /// @param v2 Destination vertex
    /// @return The edge between the vertices if found, otherwise returns nullptr
    /// @note Time Complexity: O(E), where E is the number of edges leaving the origin vertex
    static Edge* getEdge(Vertex* v1, Vertex* v2) ;

    /// @brief Gets the distance between two vertices, given their ids.
    /// @param idOrig The id of the origin vertex
    /// @param idDest The id of the destination vertex
    /// @return The distance between the vertices if found or -1 if the edge between the vertices does not exist.
    /// @note Time Complexity: O(E), where E is the number of edges leaving the origin vertex
    double getDist(unsigned int idOrig, unsigned int idDest) const;

    /// @brief Calculates the distance between two geographical coordinates using the Haversine formula.
    /// @param lat1 The latitude of the origin vertex
    /// @param long1 The longitude of the origin vertex
    /// @param lat2 The latitude of the destination vertex
    /// @param long2 The longitude of the destination vertex
    /// @return The distance between the two vertices in kilometers
    /// @note Time Complexity: O(1)
    static double calculateDist(double lat1, double long1, double lat2, double long2) ;

    /// @brief Clears the graph by removing all vertices and their associated edges.
    /// @note Time Complexity: O(V), where V is the number of vertices in the graph
    void clear();

    /// @brief Sets the graph as fully connected.
    /// @param isFullyConnected Value to set the graph's fully connected property to
    void setFullyConnected(bool isFullyConnected);

    /// @brief Sets the graph as having coordinates.
    /// @param hasCoords Value to set the graph's hasCoords property to
    void setHasCoords(bool hasCoords);

    /// @brief Gets the graph's hasCoords property.
    /// @return True if the graph uses coordinates, false otherwise
    bool usesCoords() const;

    /// @brief Gets the graph's fully connected property.
    /// @return True if the graph is fully connected, false otherwise
    bool isFullyConnected() const;
};

#endif //DA2023_PRJ2_G02_2_GRAPH_H
