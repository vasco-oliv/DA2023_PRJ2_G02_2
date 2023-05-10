#ifndef DA2023_PRJ2_G02_2_CONTROLLER_H
#define DA2023_PRJ2_G02_2_CONTROLLER_H

#include <unordered_map>
#include "Graph.h"
#include <unordered_set>

class Controller {
private:
    Graph graph;
    std::unordered_map<unsigned int,std::unique_ptr<Vertex>> vertices;

    void clearScreen();
    void dataReset();
    void readRealWorldGraph(const std::string& nodes, const std::string& edges);
    void readToyGraph(std::string edges);
    void readTourismGraph(std::string edges);
    void readOtherGraph(std::string edges);

    void backtrackingAux(Vertex *current, std::unordered_set<Vertex*>& unvisited, std::vector<Vertex*>& path, double& distance, double& bestDistance, std::vector<Vertex*>& bestPath);
public:
    //Others
    void run();

    //Menus
    void startMenu();
    void mainMenu();

    //Algorithms
    void backtracking();



};


#endif //DA2023_PRJ2_G02_2_CONTROLLER_H
