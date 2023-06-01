#ifndef DA2023_PRJ2_G02_2_CONTROLLER_H
#define DA2023_PRJ2_G02_2_CONTROLLER_H

#include "Graph.h"
#include <unordered_set>
#include <unordered_map>

#define MAX_ITERATIONS 100

class Controller {
private:
    Graph graph;
    std::vector<std::vector<double> > distances;
    std::unordered_map<unsigned int, Vertex*> vertices;

    /// @brief Clears the console screen.
    /// @note Time Complexity: O(1)
    static void clearScreen();

    /// @brief Resets the data by clearing the vertices and graph.
    /// @note Time Complexity: O(V+E), where V is the number of vertices and E is the number of edges in the graph
    void dataReset();


    /// @brief Reads the real word graphs' CSV files and populates the graph.
    /// @param nodes The name of the CSV file with the nodes
    /// @param edges The name of the CSV file with the edges
    /// @note Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges in the graph
    void readRealWorldGraph(const std::string& nodes, const std::string& edges);


    void linKernighan(std::vector<Vertex*>& path, double& distance);

    /// @brief Reads the toy graph's CSV file and populates the graph.
    /// @param edges The name of the CSV file with the edges
    /// @note Time Complexity: O(E), where E is the number of edges in the graph
    void readToyGraph(const std::string& edges);

    /// @brief Reads the extra fully connected graph's CSV file and populates the graph.
    /// @param edges The name of the CSV file with the edges
    /// @note Time Complexity: O(E), where E is the number of edges in the graph
    void readFullyConGraph(const std::string& edges);


    ///@brief Displays the start menu and allows the user to select the network graph to use (either a real world graph, a toy graph, an extra fully connected graph or another one of their choosing).
    void startMenu();

    ///@brief Displays the main menu of the program and allows the user to select which solution to the TSP should be executed (either using backtracking, the triangular aproximation heuristic or other heuristics).
    void mainMenu(); 


    /// @brief The backtracking algorithm to solve the TSP problem.
    /// @param current The current vertex being visited
    /// @param path The current path being explored
    /// @param distance The current distance of the path being explored
    /// @param bestDistance The best distance found so far
    /// @param bestPath The best path found so far
    /// @note Time Complexity: O(V!), where V is the number of vertices in the graph
    void backtrackingAux(Vertex*& current, std::vector<Vertex*>& path, double& distance, double& bestDistance, std::vector<Vertex*>& bestPath);
    
    /// @brief Executes the backtracking algorithm to solve the TSP problem.
    /// This function finds the best path and its distance and displays the results.
    /// If no path is found, it displays an error message.
    /// @note Time Complexity: O(V!), where V is the number of vertices in the graph
    void backtracking();


    /// @brief Calculates the total distance of a given path.
    /// @param path The path to calculate the distance of
    /// @return The total distance of the path
    /// @note Time Complexity: O(n), where n is the number of vertices in the path
    double calculateDistance(std::vector<Vertex*>& path);

    /// @brief Performs a preorder traversal to generate a path based on degrees of vertices.
    /// @param path The generated path
    /// @param current The current vertex being visited
    /// @param degrees The degrees of each vertex
    /// @note Time Complexity: O(V), where V is the number of vertices in the graph
    void preorder(std::vector<Vertex*>& path, Vertex* &current);
    
    /// @brief Prim's algorithm to generate a minimum spanning tree and generate the degrees of each vertex.
    /// @return The degrees of each vertex
    /// @note Time Complexity: O(E * log(V)), where V is the number of vertices and E is the number of edges in the graph
    void primMST();

    std::vector<std::vector<double>> createDistanceMatrix();

    void reverseSubpath(std::vector<Vertex*>& path, int start, int end);

    /// @brief Executes the triangular aproximation heuristic to solve the TSP problem.
    /// This function finds the best path and its distance and displays the results.
    /// If no path is found, it displays an error message.
    /// @note Time Complexity: O(V + E * log(V)), where V is the number of vertices and E is the number of edges in the graph
    void triangular();

    /// @brief Executes the nearest neighbor greedy algorithm to solve the TSP problem.
    /// This function finds the best path and its distance and displays the results.
    /// If no path is found, it displays an error message.
    /// @note Time Complexity: O(V+E), where V is the number of vertices in the graph and E is the number of edges in the graph
    void nearestNeighborGreedy(std::vector<Vertex*>& path, double& distance);
    void godsAlgorithm();

public:
    /// @brief Runs the program's start menu.
    /// @note Time Complexity: O(1)
    void run();
};


#endif //DA2023_PRJ2_G02_2_CONTROLLER_H
