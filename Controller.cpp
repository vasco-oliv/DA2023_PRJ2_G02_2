
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <unordered_set>
#include <queue>
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
    int id;
    double lat,lon;
    std::getline(ifsN,line);
    while(std::getline(ifsN,line)){
        std::istringstream iss(line);
        iss >> id;
        iss.ignore(1);
        iss >> lat;
        iss.ignore(1);
        iss >> lon;

        if(vertices.find(id)==vertices.end()){
            vertices.insert(std::make_pair(id,std::make_shared<Vertex>(id,lat,lon)));
        }

        graph.addVertex(id,lat,lon);
    }
    ifsN.close();

    std::ifstream ifsE(edges);
    if(!ifsE.is_open()){
        std::cout << "ERROR: File not found\n";
        exit(1);
    }

    std::getline(ifsE,line);
    int idOrig,idDest;
    double weight;
    while(std::getline(ifsE,line)){
        std::istringstream iss(line);
        iss >> idOrig;
        iss.ignore(1);
        iss >> idDest;
        iss.ignore(1);
        iss >> weight;

        if(vertices.find(idOrig)==vertices.end() || vertices.find(idDest)==vertices.end()){
            continue;
        }
        graph.addEdge(idOrig,idDest,weight);
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
            vertices.insert(std::make_pair(std::stoi(idOrig),std::make_shared<Vertex>(std::stoi(idOrig))));
        }
        if(vertices.find(std::stoi(idDest))==vertices.end()){
            graph.addVertex(std::stoi(idDest));
            vertices.insert(std::make_pair(std::stoi(idDest),std::make_shared<Vertex>(std::stoi(idDest))));
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
            vertices.insert(std::make_pair(std::stoi(idOrig),std::make_shared<Vertex>(std::stoi(idOrig))));
        }
        if(vertices.find(std::stoi(idDest))==vertices.end()){
            graph.addVertex(std::stoi(idDest));
            vertices.insert(std::make_pair(std::stoi(idDest),std::make_shared<Vertex>(std::stoi(idDest))));
        }
        graph.addEdge(std::stoi(idOrig),std::stoi(idDest),std::stod(weight));

    }
}

void Controller::readFullyConGraph(std::string edges) {
    std::ifstream ifs(edges);
    if(!ifs.is_open()){
        std::cout << "ERROR: File not found\n";
        exit(1);
    }
    std::string line;
    int idOrig, idDest;
    double weight;
    while(std::getline(ifs,line)){
        std::istringstream iss(line);
        iss >> idOrig;
        iss.ignore(1);
        iss >> idDest;
        iss.ignore(1);
        iss >> weight;

        if(vertices.find(idOrig)==vertices.end()){
            graph.addVertex(idOrig);
            vertices.insert(std::make_pair(idOrig,std::make_shared<Vertex>(idOrig)));
        }
        if(vertices.find(idDest)==vertices.end()){
            graph.addVertex(idDest);
            vertices.insert(std::make_pair(idDest,std::make_shared<Vertex>(idDest)));
        }
        graph.addEdge(idOrig,idDest,weight);

    }
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
    std::cout << "3. Extra Fully Connected Graphs\n";
    std::cout << "4. Other Graph\n";
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
            readFullyConGraph("../Project2Graphs/Extra_Fully_Connected_Graphs/edges_25.csv");
            mainMenu();
            break;
        case 4:
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
            clearScreen();
            std::cout << "Calculating best solution using Backtracking...\n";
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

void Controller::backtrackingAux(std::shared_ptr<Vertex> current, std::vector<std::shared_ptr<Vertex>>& path, double& distance, double& bestDistance, std::vector<std::shared_ptr<Vertex>>& bestPath) {
    if(distance >= bestDistance){
        return;
    }
    current->setVisited(true);
    path.push_back(current);
    if (path.size() == graph.getVertexSet().size()) {
        for(const auto& edge : current->getAdj()){
            if (edge->getDest().get() == graph.getVertexSet()[0].get()) {
                distance += edge->getWeight();
                path.push_back(graph.getVertexSet()[0]);
                if(distance < bestDistance){
                    bestDistance = distance;
                    bestPath = std::vector<std::shared_ptr<Vertex>>(path);
                    std::cout << path[1]->getId() << ' ' << bestDistance << std::endl;
                }
                distance -= edge->getWeight();
                path.pop_back();
                break;
            }
        }
        path.pop_back();
        current->setVisited(false);
        return;
    }

    std::priority_queue<std::shared_ptr<Edge>, std::vector<std::shared_ptr<Edge>>, EdgeComparator> pq(current -> getAdj().begin(), current -> getAdj().end());
    while(!pq.empty()){
        auto edge = pq.top();
        pq.pop();
        std::shared_ptr<Vertex> dest = edge->getDest();
        double weight = edge->getWeight();
        if(distance+weight >= bestDistance) break;
        if (!dest->isVisited()) {
            distance += weight;
            dest->setVisited(true);
            backtrackingAux(dest,path,distance,bestDistance,bestPath);
            dest->setVisited(false);
            distance -= weight;
        }
    }

    path.pop_back();
    current->setVisited(false);
}

void Controller::backtracking() {
    std::vector<std::shared_ptr<Vertex>> path, bestPath;
    double distance = 0, bestDistance = std::numeric_limits<double>::max();
    for (const auto& vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
    }
    backtrackingAux(graph.getVertexSet()[0], path, distance, bestDistance, bestPath);

    clearScreen();
    std::cout << "\t**Traveling Salesperson Problem**\n\n";
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

std::shared_ptr<Vertex> Controller::findNearestNeighbor(std::shared_ptr<Vertex> current) {
    for (const auto& edge : current->getAdj()) {
        if (!edge->getDest()->isVisited()) {
            return edge->getDest();
        }
    }
    return nullptr;
}

void Controller::nearestNeighborGreedy(std::vector<std::shared_ptr<Vertex>> &path, double &distance) {
    std::shared_ptr<Vertex> current = graph.getVertexSet()[0];

    while (true) {
      if (findNearestNeighbor(current) == nullptr) {
        distance += current->getAdj()[0]->getWeight();
        path.push_back(current);
        break;
      }
    }
}
