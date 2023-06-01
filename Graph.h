#ifndef DA2023_PRJ2_G02_2_GRAPH_H
#define DA2023_PRJ2_G02_2_GRAPH_H

#include <vector>
#include <memory>
#include "VertexEdge.h"

class Graph {
private:
    std::vector<Vertex*> vertexSet;
    bool isFullyConnected = false;
    bool hasCoords = false;
public:


    /// @brief Gets all the vertices in the graph.
    /// @return A vector with all the vertices in the graph
    /// @note Time Complexity: O(1)
    const std::vector<Vertex *> & getVertexSet() const;

    /// @brief Finds a vertex in the graph, given its id.
    /// @param id The id of the vertex to find
    /// @return An iterator to the vertex if found, otherwise returns the end of the vertex set
    /// @note Time Complexity: O(V), where V is the number of vertices in the graph
    Vertex* findVertex(unsigned int id) const;

    /// @brief Adds a vertex to the graph, given its id.
    /// @param id The id of the vertex to add
    /// @return True if the vertex was added, false otherwise
    /// @note Time Complexity: O(V), where V is the number of vertices in the graph
    bool addVertex(unsigned int id);

    /// @brief Adds a vertex to the graph, given its id, latitude and longitude.
    /// @param id The id of the vertex to add
    /// @param latitude The latitude of the vertex to add
    /// @param longitude The longitude of the vertex to add
    /// @return True if the vertex was added, false otherwise
    /// @note Time Complexity: O(V), where V is the number of vertices in the graph
    bool addVertex(unsigned int id, double latitude, double longitude);

    /// @brief Adds a vertex to the graph.
    /// @param vertex The vertex to add
    /// @return True if the vertex was added, false otherwise
    /// @note Time Complexity: O(V), where V is the number of vertices in the graph
    void addVertex(Vertex* vertex);

    /// @brief Removes a vertex from the graph, given its id.
    /// @param id The id of the vertex to remove
    /// @return True if the vertex was removed, false otherwise
    /// @note Time Complexity: O(V), where V is the number of vertices in the graph
    //bool removeVertex(unsigned int id);

    /// @brief Adds an edge to the graph, given the ids of its origin and destination vertices and its weight.
    /// @param idOrig The id of the origin vertex of the edge to add
    /// @param idDest The id of the destination vertex of the edge to add
    /// @param weight The weight of the edge to add
    /// @return True if the edge was added, false otherwise
    /// @note Time Complexity: O(V), where V is the number of vertices in the graph
    void addEdge(unsigned int idOrig, unsigned int idDest, double weight);

    void addEdge(Vertex* v1, Vertex* v2, double weight);

    /// @brief Gets the distance between two vertices, given their ids.
    /// @param idOrig The id of the origin vertex
    /// @param idDest The id of the destination vertex
    /// @return The distance between the vertices if found, 0 if either the origin or destination vertex was not found, or -1 if the edge between the vertices does not exist.
    /// @note Time Complexity: O(E), where E is the number of edges leaving the origin vertex
    double getDist(unsigned int idOrig, unsigned int idDest) const;

    /// @brief Gets the distance between two vertices, given their ids.
    /// @param idOrig The id of the origin vertex
    /// @param idDest The id of the destination vertex
    /// @return The distance between the vertices if found, 0 if either the origin or destination vertex was not found, or -1 if the edge between the vertices does not exist.
    Edge* getEdge(Vertex* v1, Vertex* v2) const;

    /// @brief Gets the distance between two vertices.
    /// @param v1 The origin vertex
    /// @param v2 The destination vertex
    /// @return The distance between the vertices if found, 0 if either the origin or destination vertex was not found, or -1 if the edge between the vertices does not exist.
    /// @note Time Complexity: O(E), where E is the number of edges leaving v1
    double getDist(Vertex *v1, Vertex *v2) const;

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
    /// @note Time Complexity: O(1)
    void setFullyConnected(bool isFullyConnected);

    /// @brief Sets the graph as having coordinates.
    /// @param hasCoords Value to set the graph's hasCoords property to
    /// @note Time Complexity: O(1)
    void setHasCoords(bool hasCoords);

    /// @brief Gets the graph's fully connected property.
    /// @return True if the graph uses coordinates, false otherwise
    bool usesCoords() const;

    /// @brief Gets the graph's hasCoords property.
    /// @return True if the graph is fully connected, false otherwise
    bool fullyConnected() const;

};

#endif //DA2023_PRJ2_G02_2_GRAPH_H
