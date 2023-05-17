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

    void backtrackingAux(Vertex *current, std::vector<Vertex*>& path, double& distance, double& bestDistance, std::vector<Vertex*>& bestPath);
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
