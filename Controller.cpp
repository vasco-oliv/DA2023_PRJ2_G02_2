
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Controller.h"

void Controller::clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    // Assume POSIX
        std::system("clear");
#endif
}

void Controller::dataReset() {
    //rip data
}

void Controller::readRealWorldGraph(const std::string& nodes, const std::string& edges) {
    std::ifstream ifsN(nodes);
    if(!ifsN.is_open()){
        std::cout << "ERROR: File not found\n";
        exit(1);
    }

    std::string line;
    std::getline(ifsN,line);
    while(std::getline(ifsN,line)){
        std::istringstream iss(line);
        std::string id,lat,lon;
        std::getline(iss,id,',');
        std::getline(iss,lat,',');
        std::getline(iss,lon);
        if(id.empty() || lat.empty() || lon.empty()){
            continue;
        }

        if(vertices.find(std::stoi(id))==vertices.end()){
            vertices.insert(std::make_pair(std::stoi(id),std::make_unique<Vertex>(std::stoi(id),std::stod(lat),std::stod(lon))));
        }

        graph.addVertex(std::stoi(id),std::stod(lat),std::stod(lon));
    }
    ifsN.close();

    std::ifstream ifsE(edges);
    if(!ifsE.is_open()){
        std::cout << "ERROR: File not found\n";
        exit(1);
    }

    std::getline(ifsE,line);
    while(std::getline(ifsE,line)){
        std::istringstream iss(line);
        std::string idOrig,idDest,weight;
        std::getline(iss,idOrig,',');
        std::getline(iss,idDest,',');
        std::getline(iss,weight);
        if(idOrig.empty() || idDest.empty() || weight.empty()){
            continue;
        }
        if(vertices.find(std::stoi(idOrig))==vertices.end() || vertices.find(std::stoi(idDest))==vertices.end()){
            continue;
        }
        graph.addEdge(std::stoi(idOrig),std::stoi(idDest),std::stod(weight));
    }

}

void Controller::readToyGraph(std::string edges) {
    std::ifstream ifs(edges);
    if(!ifs.is_open()){
        std::cout << "ERROR: File not found\n";
        exit(1);
    }
    std::string line;
    getline(ifs,line);
    while(std::getline(ifs,line)){
        std::istringstream iss(line);
        std::string idOrig,idDest,weight;
        std::getline(iss,idOrig,',');
        std::getline(iss,idDest,',');
        std::getline(iss,weight);
        if(idOrig.empty() || idDest.empty() || weight.empty()){
            continue;
        }
        if(vertices.find(std::stoi(idOrig))==vertices.end()){
            graph.addVertex(std::stoi(idOrig));
            vertices.insert(std::make_pair(std::stoi(idOrig),std::make_unique<Vertex>(std::stoi(idOrig))));
        }
        if(vertices.find(std::stoi(idDest))==vertices.end()){
            graph.addVertex(std::stoi(idDest));
            vertices.insert(std::make_pair(std::stoi(idDest),std::make_unique<Vertex>(std::stoi(idDest))));
        }
        graph.addEdge(std::stoi(idOrig),std::stoi(idDest),std::stod(weight));

    }
}

void Controller::readOtherGraph(std::string edges) {
    readToyGraph(edges);
}


void Controller::run() {
    startMenu();
}

void Controller::startMenu() {
    clearScreen();
    std::cout << "\t**Start Menu**\n\n";
    std::cout << "Select a Network Graph:\n";
    std::cout << "1. Real World Graphs\n";
    std::cout << "2. Toy Graphs\n";
    std::cout << "3. Other Graph\n";
    std::cout << "0. Exit\n";
    std::cout << "Option: ";
    int option,option2;
    std::string aux;
    std::cin >> option;
    switch (option) {
        case 1:
            clearScreen();
            std::cout << "\t**Start Menu**\n\n";
            std::cout << "Select a Real World Graph:\n";
            std::cout << "1. Graph1\n";
            std::cout << "2. Graph2\n";
            std::cout << "3. Graph3\n";
            std::cout << "0. Go Back\n";
            std::cout << "Option: ";
            std::cin >> option2;
            switch (option2) {
                case 1:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readRealWorldGraph("../Project2Graphs/Real-World-Graphs/graph1/nodes.csv","../Project2Graphs/Real-World-Graphs/graph1/edges.csv");
                    mainMenu();
                    break;
                case 2:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readRealWorldGraph("../Project2Graphs/Real-World-Graphs/graph2/nodes.csv","../Project2Graphs/Real-World-Graphs/graph2/edges.csv");
                    mainMenu();
                    break;
                case 3:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readRealWorldGraph("../Project2Graphs/Real-World-Graphs/graph3/nodes.csv","../Project2Graphs/Real-World-Graphs/graph3/edges.csv");
                    mainMenu();
                    break;
                case 0:
                    startMenu();
                    break;
                default:
                    std::cout << "ERROR: Invalid option\n";
                    std::cout << "(Press any key to continue)";
                    std::cin >> aux;
                    startMenu();
                    break;
            }
            break;
        case 2:
            clearScreen();
            std::cout << "\t**Start Menu**\n\n";
            std::cout << "Select a Real World Graph:\n";
            std::cout << "1. Shipping\n";
            std::cout << "2. Stadiums\n";
            std::cout << "3. Tourism\n";
            std::cout << "0. Go Back\n";
            std::cout << "Option: ";
            std::cin >> option2;
            switch(option2){
                case 1:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readToyGraph("../Project2Graphs/Toy-Graphs/shipping.csv");
                    mainMenu();
                    break;
                case 2:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readToyGraph("../Project2Graphs/Toy-Graphs/stadiums.csv");
                    mainMenu();
                    break;
                case 3:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readToyGraph("../Project2Graphs/Toy-Graphs/tourism.csv");
                    mainMenu();
                    break;
                case 0:
                    startMenu();
                    break;
                default:
                    std::cout << "ERROR: Invalid option\n";
                    std::cout << "(Press any key to continue)";
                    std::cin >> aux;
                    startMenu();
                    break;
            }
            break;
        case 3:
            std::cout << "Other Graph\n";
            break;
        case 0:
            std::cout << "Exit\n";
            break;
        default:
            std::cout << "ERROR: Invalid option\n";
            break;
    }
}

void Controller::mainMenu() {
    clearScreen();
    std::cout << "\t**Traveling Salesperson Problem**\n\n";
    std::cout << "How would you like to calculate the best solution to the TSP in the graph you selected?\n";
    std::cout << "1. Backtracking\n";
    std::cout << "2. Triangular Approximation Heuristic\n";
    std::cout << "3. Other Heuristic\n";
    std::cout << "4. Change Graph\n";
    std::cout << "0. Exit\n";
    std::cout << "Option: ";
    int option;
    std::string aux;
    std::cin >> option;
    switch (option) {
        case 1:
            //backtracking();
            break;
        case 2:
            //triangular();
            break;
        case 3:
            //algoritmo_dos_deuses();
            break;
        case 4:
            //data.clear();
            startMenu();
            break;
        case 0:
            break;
        default:
            std::cout << "ERROR: Invalid option\n";
            std::cout << "(Press any key to continue)";
            std::cin >> aux;
            mainMenu();
            break;
    }

}

void Controller::backtracking(unsigned int startNode) {
    std::vector<unsigned int> path;
    std::vector<unsigned int> visited;
    int cost = backtrackingAux(startNode, path, visited);
    std::cout << "Path: ";
    for (unsigned int i = 0; i < path.size(); i++) {
        std::cout << path[i] << " ";
    }
    std::cout << "\nCost: " << cost << "\n";
    std::cout << "(Press any key to continue)";
    std::string aux;
    std::cin >> aux;
    mainMenu();
}


int Controller::backtrackingAux(unsigned int startNode, std::vector<unsigned int> &path, std::vector<unsigned int> &visited) {
    return 0;
}


