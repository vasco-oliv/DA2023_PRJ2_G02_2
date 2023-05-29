#ifndef DA2023_PRJ2_G02_2_CONTROLLER_H
#define DA2023_PRJ2_G02_2_CONTROLLER_H

#include "Graph.h"
#include <unordered_set>
#include <map>

class Controller {
private:
    Graph graph;
    std::map<unsigned int,std::shared_ptr<Vertex>> vertices;

    void clearScreen();
    void dataReset();
    void readRealWorldGraph(const std::string& nodes, const std::string& edges);
    void readToyGraph(std::string edges);
    void readTourismGraph(std::string edges);
    void readFullyConGraph(std::string edges);

    void backtrackingAux(const std::shared_ptr<Vertex>& current, std::vector<std::shared_ptr<Vertex>>& path, double& distance, double& bestDistance, std::vector<std::shared_ptr<Vertex>>& bestPath);
    void nearestNeighborGreedy(std::vector<std::shared_ptr<Vertex>>& path, double& distance);
    void primMST(std::vector<std::shared_ptr<Vertex>>& path);
    double calculateDistance(std::vector<std::shared_ptr<Vertex>>& path);
public:
    //Others
    void run();

    //Menus
    void startMenu();
    void mainMenu();

    //Algorithms
    void backtracking();
    void triangular();



};


#endif //DA2023_PRJ2_G02_2_CONTROLLER_H
