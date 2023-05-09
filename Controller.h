#ifndef DA2023_PRJ2_G02_2_CONTROLLER_H
#define DA2023_PRJ2_G02_2_CONTROLLER_H

#include <unordered_map>
#include "Graph.h"

class Controller {
private:
    Graph graph;
    std::unordered_map<unsigned int,std::unique_ptr<Vertex>> vertices;

    void clearScreen();
    void dataReset();
    void readRealWorldGraph(const std::string& nodes, const std::string& edges);
    void readToyGraph(std::string edges);
    void readOtherGraph(std::string edges);

    int backtrackingAux(unsigned int startNode, std::vector<unsigned int> &path, std::vector<unsigned int> &visited);
public:
    //Others
    void run();

    //Menus
    void startMenu();
    void mainMenu();

    //Algorithms
    void backtracking(unsigned int startNode=0);



};


#endif //DA2023_PRJ2_G02_2_CONTROLLER_H
