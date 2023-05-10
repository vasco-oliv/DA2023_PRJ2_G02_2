
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <unordered_set>
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

void Controller::readTourismGraph(std::string edges) {
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
        std::getline(iss,weight,',');
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
            backtracking();
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

void Controller::backtrackingAux(Vertex *current, std::unordered_set<Vertex*>& unvisited, std::vector<Vertex*>& path, double& distance, double& bestDistance, std::vector<Vertex*>& bestPath) {
    current->setVisited(true);
    path.push_back(current);
    for (const auto& edge : current->getAdj()) {
        Vertex *dest = edge->getDest();
        if (!dest->isVisited()) {
            double weight = edge->getWeight();
            distance += weight;
            unvisited.erase(dest);
            backtrackingAux(dest, unvisited, path, distance, bestDistance, bestPath);
            unvisited.insert(dest);
            distance -= weight;
        }
    }
    if (unvisited.empty()) {
        for (const auto& edge : current->getAdj()) {
            if (edge->getDest() == graph.getVertexSet()[0].get()) {
                distance += edge->getWeight();
                path.push_back(graph.getVertexSet()[0].get());
                break;
            }
        }
        if (path.size() == graph.getVertexSet().size()+1  && distance < bestDistance) {
            bestDistance = distance;
            bestPath = std::vector<Vertex*>(path);
        }
    }

    path.pop_back();
    current->setVisited(false);
}

void Controller::backtracking() {
    std::unordered_set<Vertex*> unvisited;
    std::vector<Vertex*> path, bestPath;
    double distance = 0, bestDistance = std::numeric_limits<double>::max();
    for (const auto& vertex : graph.getVertexSet()) {
        unvisited.insert(vertex.get());
    }
    unvisited.erase(graph.getVertexSet()[0].get());
    backtrackingAux(graph.getVertexSet()[0].get(), unvisited, path, distance, bestDistance, bestPath);
    unvisited.insert(graph.getVertexSet()[0].get());

    std::cout << "Best Path: ";
    std::cout << bestPath[0]->getId();
    for (int i = 1; i < bestPath.size(); ++i) {
        std::cout << " -> " << bestPath[i]->getId();
    }
    std::cout << "\nBest Distance: " << bestDistance << "\n";
    std::cout << "(Press any key to continue)\n";
    std::string aux;
    std::cin >> aux;
    mainMenu();
}

