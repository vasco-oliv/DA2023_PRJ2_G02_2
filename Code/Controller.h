#ifndef DA2023_PRJ2_G02_2_CONTROLLER_H
#define DA2023_PRJ2_G02_2_CONTROLLER_H

#include "Graph.h"
#include <unordered_set>
#include <unordered_map>


class Controller {
private:
    Graph graph;
    std::vector<std::vector<double> > distances;
    std::unordered_map<unsigned int, Vertex*> vertices;

    /// @brief Clears the console screen.
    static void clearScreen();

    /// @brief Resets the data by clearing the vertices and graph.
    /// @note Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges in the graph
    void dataReset();

    /// @brief Creates a matrix with the distances between each pair of vertices.
    /// @return The matrix with the distances between each pair of vertices
    /// @note Time Complexity: O(V^2), where V is the number of vertices in the graph
    std::vector<std::vector<double>> createDistanceMatrix();

    /// @brief Reads the real word graphs' CSV files, populates the graph and creates its distances matrix.
    /// @param nodes The name of the CSV file with the nodes
    /// @param edges The name of the CSV file with the edges
    /// @note Time Complexity: O(V ^2 + E), where V is the number of vertices and E is the number of edges in the graph
    void readRealWorldGraph(const std::string& nodes, const std::string& edges);

    /// @brief Reads the toy graph's CSV file, populates the graph and creates its distances matrix.
    /// @param edges The name of the CSV file with the edges
    /// @note Time Complexity: O(V^2 + E), where V is the number of vertices and E is the number of edges in the graph
    void readToyGraph(const std::string& edges);

    /// @brief Reads the extra fully connected graph's CSV file, populates the graph and creates its distances matrix.
    /// @param edges The name of the CSV file with the edges
    /// @note Time Complexity: O(V^2 + E), where V is the number of vertices and E is the number of edges in the graph
    void readFullyConGraph(const std::string& edges);

    /// @brief Displays the start menu and allows the user to select the network graph to use (either a real world graph, a toy graph, an extra fully connected graph or another one of their choosing).
    void startMenu();

    /// @brief Displays the main menu of the program and allows the user to select which solution to the TSP should be executed (either using backtracking, the triangular aproximation heuristic or other heuristics).
    void mainMenu(); 

    /// @brief The backtracking algorithm to solve the TSP problem.
    /// @param current The current vertex being visited
    /// @param path The current path being explored
    /// @param distance The current distance of the path being explored
    /// @param bestDistance The best distance found so far
    /// @param bestPath The best path found so far
    /// @note Time Complexity: O((V - 1)!), where V is the number of vertices in the graph
    void backtrackingAux(Vertex*& current, std::vector<Vertex*>& path, double& distance, double& bestDistance, std::vector<Vertex*>& bestPath);
    
    /// @brief Executes the backtracking algorithm to solve the TSP problem.
    /// This function finds the best path and its distance and displays the results.
    /// If no path is found, it displays an error message.
    /// @note Time Complexity: O((V - 1)!), where V is the number of vertices in the graph
    void backtracking();

    /// @brief Performs a preorder traversal to generate a path based on degrees of vertices.
    /// @param path The generated path
    /// @param current The current vertex being visited
    /// @param degrees The degrees of each vertex
    /// @return The total distance of the path
    /// @note Time Complexity: O(V), where V is the number of vertices in the graph
    double preorder(std::vector<Vertex*>& path, Vertex* &current);
    
    /// @brief Prim's algorithm to generate a minimum spanning tree and generate the degrees of each vertex.
    /// @return The degrees of each vertex
    /// @note Time Complexity: O(V^2 + E), where V is the number of vertices and E is the number of edges in the graph
    void primMST();

    /// @brief Executes the triangular approximation heuristic to solve the TSP problem.
    /// This function finds the best path and its distance and displays the results.
    /// If no path is found, it displays an error message.
    /// @note Time Complexity: O(V^2 + E), where V is the number of vertices and E is the number of edges in the graph
    void triangular();

    /// @brief Executes the nearest neighbor greedy algorithm to solve the TSP problem.
    /// This function finds the best path and its distance and displays the results.
    /// If no path is found, it displays an error message.
    /// @note Time Complexity: O(V + E), where V is the number of vertices in the graph and E is the number of edges in the graph
    void nearestNeighborGreedy(std::vector<Vertex*>& path, double& distance);

    /// @brief Reverses a subpath of a given path.
    /// @param path The path to reverse the subpath of
    /// @param start The starting index of the subpath
    /// @param end The ending index of the subpath
    /// @note Time Complexity: O(V), where V is the number of vertices in the subpath
    void reverseSubpath(std::vector<Vertex*>& path, int start, int end);

    /// @brief The Lin Kernighan algorithm to solve the TSP problem.
    /// @param path The path to improve
    /// @param distance The distance of the path to improve
    /// @note Time Complexity: O(V^3), where V is the number of vertices in the graph
    void linKernighan(std::vector<Vertex*>& path, double& distance);

    /// @brief Executes the chained Lin Kernighan algorithm to solve the TSP problem.
    /// This function finds the best path and its distance and displays the results.
    /// If no path is found, it displays an error message.
    /// @note Time Complexity: O(V^3), where V is the number of vertices in the graph
    void LK();

public:
    /// @brief Runs the program's start menu.
    void run();
};


#endif //DA2023_PRJ2_G02_2_CONTROLLER_H
