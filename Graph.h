#ifndef DA2023_PRJ2_G02_2_GRAPH_H
#define DA2023_PRJ2_G02_2_GRAPH_H

#include <vector>
#include <memory>
#include "VertexEdge.h"

class Graph {
private:
    std::vector<std::shared_ptr<Vertex>> vertexSet;

public:
    bool hasCoords = false;

    /// @brief Gets all the vertices in the graph.
    /// @return A vector with all the vertices in the graph
    /// @note Time Complexity: O(1)
    const std::vector<std::shared_ptr<Vertex>>& getVertexSet() const;

    /// @brief Finds a vertex in the graph, given its id.
    /// @param id The id of the vertex to find
    /// @return An iterator to the vertex if found, otherwise returns the end of the vertex set
    /// @note Time Complexity: O(V), where V is the number of vertices in the graph
    std::vector<std::shared_ptr<Vertex>>::const_iterator findVertex(unsigned int id) const;

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
    bool addVertex(const std::shared_ptr<Vertex>& vertex);

    /// @brief Removes a vertex from the graph, given its id.
    /// @param id The id of the vertex to remove
    /// @return True if the vertex was removed, false otherwise
    /// @note Time Complexity: O(V), where V is the number of vertices in the graph
    bool removeVertex(unsigned int id);

    /// @brief Adds an edge to the graph, given the ids of its origin and destination vertices and its weight.
    /// @param idOrig The id of the origin vertex of the edge to add
    /// @param idDest The id of the destination vertex of the edge to add
    /// @param weight The weight of the edge to add
    /// @return True if the edge was added, false otherwise
    /// @note Time Complexity: O(V), where V is the number of vertices in the graph
    bool addEdge(unsigned int idOrig, unsigned int idDest, double weight);

    /// @brief Gets the distance between two vertices, given their ids.
    /// @param idOrig The id of the origin vertex
    /// @param idDest The id of the destination vertex
    /// @return The distance between the vertices if found, 0 if either the origin or destination vertex was not found, or -1 if the edge between the vertices does not exist.
    /// @note Time Complexity: O(E), where E is the number of edges leaving the origin vertex
    double getDist(unsigned int idOrig, unsigned int idDest) const;

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
};

#endif //DA2023_PRJ2_G02_2_GRAPH_H
