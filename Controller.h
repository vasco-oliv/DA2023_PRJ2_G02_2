#ifndef DA2023_PRJ2_G02_2_CONTROLLER_H
#define DA2023_PRJ2_G02_2_CONTROLLER_H

#include "Graph.h"
#include <unordered_set>
#include <unordered_map>

class Controller {
private:
    Graph graph;
    std::unordered_map<unsigned int, std::shared_ptr<Vertex>> vertices;

    static void clearScreen();
    void dataReset();
    void readRealWorldGraph(const std::string& nodes, const std::string& edges);
    void readToyGraph(std::string edges);
    void readFullyConGraph(std::string edges);

    void backtrackingAux(const std::shared_ptr<Vertex>& current, std::vector<std::shared_ptr<Vertex>>& path, double& distance, double& bestDistance, std::vector<std::shared_ptr<Vertex>>& bestPath);
    void nearestNeighborGreedy(std::vector<std::shared_ptr<Vertex>>& path, double& distance);
    void linKernighan(std::vector<std::shared_ptr<Vertex>>& path, double& distance);

    std::vector<std::vector<unsigned int>> primMST();
    double calculateDistance(std::vector<std::shared_ptr<Vertex>>& path);
    void preorder(std::vector<std::shared_ptr<Vertex>>& path, const std::shared_ptr<Vertex>& current, std::vector<std::vector<unsigned int>>& degrees);

    void startMenu();
    void mainMenu();

    void backtracking();
    void triangular();
    void godsAlgorithm();
public:
    void run();

};


#endif //DA2023_PRJ2_G02_2_CONTROLLER_H
