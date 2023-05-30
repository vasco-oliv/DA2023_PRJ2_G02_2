#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
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
    clearScreen();
    std::cout << "Clearing data...\n";
    vertices.clear();
    graph.clear();
    graph = Graph();
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

    std::getline(ifsN, line);

    while(std::getline(ifsN, line)){
        std::istringstream iss(line);
        iss >> id;
        iss.ignore(1);
        iss >> lat;
        iss.ignore(1);
        iss >> lon;

        if(vertices.find(id)==vertices.end()){
            auto v = std::make_shared<Vertex>(id,lat,lon);
            vertices.insert(std::make_pair(id,v));
            graph.addVertex(v);
        }

    }
    ifsN.close();

    std::ifstream ifsE(edges);
    if(!ifsE.is_open()){
        std::cout << "ERROR: File not found\n";
        exit(1);
    }

    std::getline(ifsE, line);

    int idOrig,idDest;
    double weight;

    while(std::getline(ifsE, line)){
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
    graph.hasCoords = true;
}

void Controller::readToyGraph(std::string edges) {
    std::ifstream ifs(edges);

    if(!ifs.is_open()){
        std::cout << "ERROR: File not found\n";
        exit(1);
    }

    std::string line;
    getline(ifs, line);

    int idOrig, idDest;
    double weight;

    while(std::getline(ifs, line)){
        std::istringstream iss(line);
        iss >> idOrig;
        iss.ignore(1);
        iss >> idDest;
        iss.ignore(1);
        iss >> weight;

        if(vertices.find(idOrig) == vertices.end()){
            auto v = std::make_shared<Vertex>(idOrig);
            vertices.insert(std::make_pair(idOrig, v));
            graph.addVertex(v);
        }
        if(vertices.find(idDest) == vertices.end()){
            auto v = std::make_shared<Vertex>(idDest);
            vertices.insert(std::make_pair(idDest, v));
            graph.addVertex(v);
        }
        graph.addEdge(idOrig, idDest, weight);
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
            auto v = std::make_shared<Vertex>(idOrig);
            vertices.insert(std::make_pair(idOrig,v));
            graph.addVertex(v);
        }
        if(vertices.find(idDest)==vertices.end()){
            auto v = std::make_shared<Vertex>(idDest);
            vertices.insert(std::make_pair(idDest,v));
            graph.addVertex(v);
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

    int option, option2;
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
            std::cout << "Select a Toy Graph:\n";
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
            readFullyConGraph("../Project2Graphs/Extra_Fully_Connected_Graphs/edges_900.csv");
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
            triangular();
            break;
        case 3:
            //algoritmo_dos_deuses();
            break;
        case 4:
            dataReset();
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

void Controller::backtrackingAux(const std::shared_ptr<Vertex>& current, std::vector<std::shared_ptr<Vertex>>& path, double& distance, double& bestDistance, std::vector<std::shared_ptr<Vertex>>& bestPath) {
    if(distance >= bestDistance) return;

    current->setVisited(true);
    path.push_back(current);

    if (path.size() == graph.getVertexSet().size()) {
        for(const auto& edge : current->getAdj()){
            if (edge->getDest().get() == graph.getVertexSet()[0].get()) {
                distance += edge->getWeight();
                path.push_back(graph.getVertexSet()[0]);

                if(distance < bestDistance - std::numeric_limits<float>::epsilon()){
                    bestDistance = distance;
                    bestPath = std::vector<std::shared_ptr<Vertex>>(path);
                    std::cout << path[1]->getId() << " " << bestDistance << std::endl;
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
            backtrackingAux(dest, path, distance, bestDistance, bestPath);
            dest->setVisited(false);
            distance -= weight;
        }
    }

    path.pop_back();
    current->setVisited(false);
}

void Controller::backtracking() {
    clock_t start = clock();
    std::vector<std::shared_ptr<Vertex>> path, bestPath;
    double distance = 0, bestDistance = std::numeric_limits<double>::max();

    for (const auto& vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
    }

    backtrackingAux(graph.getVertexSet()[0], path, distance, bestDistance, bestPath);

    clock_t end = clock();
    clearScreen();
    std::cout << "\t**Traveling Salesperson Problem**\n\n";

    if(bestPath.size() == 1){
        std::cout << "No path found!\n";
        std::cout << "Time: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds\n";
        std::cout << "(Press any key to continue)\n";
        std::string aux;
        std::cin >> aux;
        mainMenu();
    }

    std::cout << "Best Path: ";
    std::cout << bestPath[0]->getId();

    for (int i = 1; i < bestPath.size(); ++i) {
        std::cout << " -> " << bestPath[i]->getId();
    }

    std::cout << "\nBest Distance: " << bestDistance << "\n";
    std::cout << "Time: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds\n";
    std::cout << "(Press any key to continue)\n";
    std::string aux;
    std::cin >> aux;
    mainMenu();
}

double Controller::calculateDistance(std::vector<std::shared_ptr<Vertex>> &path) {
    double distance=0;
    for(int i = 0; i < path.size()-1; i++){
        double w = graph.getDist(path[i]->getId(),path[i+1]->getId());
        if(w == -1){
            if(!graph.hasCoords) return -1;
            else {
                w = graph.calculateDist(path[i]->getLatitude(),path[i]->getLongitude(),path[i+1]->getLatitude(),path[i+1]->getLongitude());
            }
        }
        distance += w;
    }
    return distance;
}

void Controller::preorder(std::vector<std::shared_ptr<Vertex>>& path,const std::shared_ptr<Vertex>& current, std::vector<std::vector<unsigned int>>& degrees) {
    path.push_back(current);
    current->setVisited(true);

    if(degrees.size() <= current->getDist()+1) return;

    for(auto v: degrees[current->getDist()+1]){
        if(vertices.find(v) == vertices.end()) continue;

        if(!vertices[v]->isVisited() && vertices[v]->getPrevious() == current->getId()){
            preorder(path, vertices[v], degrees);
        }
    }
}

std::vector<std::vector<unsigned int>> Controller::primMST() {
    auto current = graph.getVertexSet()[0];
    current->setDist(0);
    std::vector<std::vector<unsigned int>> degrees(graph.getVertexSet().size());
    current->setVisited(true);
    degrees[0].push_back(current->getId());
    std::priority_queue<std::shared_ptr<Edge>, std::vector<std::shared_ptr<Edge>>, EdgeComparator> pq(current -> getAdj().begin(), current -> getAdj().end());

    while(!pq.empty()){
        auto edge = pq.top();
        pq.pop();
        std::shared_ptr<Vertex> dest = edge->getDest();

        if (!dest->isVisited()) {
            dest->setVisited(true);
            dest->setPrevious(current->getId());
            dest->setDist(current->getDist()+1);

            degrees[dest->getDist()].push_back(dest->getId());
            
            current = dest;

            for(const auto& edge2 : current->getAdj()){
                if(!edge2->getDest()->isVisited()){
                    pq.push(edge2);
                }
            }
        }
    }
    return degrees;
}

void Controller::triangular() {
    clock_t start = clock();
    std::vector<std::shared_ptr<Vertex>> path;

    for (const auto& vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
    }

    auto degrees = primMST();

    for (const auto& vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
    }

    preorder(path, graph.getVertexSet()[0],degrees);
    path.push_back(graph.getVertexSet()[0]);
    clock_t end = clock();
    clearScreen();

    if(path.size() == 1){
        std::cout << "No path found!\n";
        std::cout << "Time: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds\n";
        std::cout << "(Press any key to continue)\n";
        std::string aux;
        std::cin >> aux;
        mainMenu();
    }

    std::cout << "\t**Traveling Salesperson Problem**\n\n";
    std::cout << "Best Path: ";
    std::cout << path[0]->getId();

    for (int i = 1; i < path.size(); ++i) {
        std::cout << " -> " << path[i]->getId();
    }

    std::cout << "\nBest Distance: " << calculateDistance(path) << "\n";
    std::cout << "Time: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds\n";
    std::cout << "(Press any key to continue)\n";
    std::string aux;
    std::cin >> aux;
    mainMenu();
}

void Controller::nearestNeighborGreedy(std::vector<std::shared_ptr<Vertex>> &path, double &distance) {
    std::shared_ptr<Vertex> current = graph.getVertexSet()[0];
    current->setVisited(true);
    path.push_back(current);

    while(path.size() < graph.getVertexSet().size()){
        std::priority_queue<std::shared_ptr<Edge>, std::vector<std::shared_ptr<Edge>>, EdgeComparator> pq(current -> getAdj().begin(), current -> getAdj().end());
        while(!pq.empty()){
            auto edge = pq.top();
            pq.pop();

            std::shared_ptr<Vertex> dest = edge->getDest();
            double weight = edge->getWeight();

            if (!dest->isVisited()) {
                distance += weight;
                dest->setVisited(true);
                path.push_back(dest);
                current = dest;
                break;
            }
        }
    }
    path.push_back(graph.getVertexSet()[0]);
    distance += graph.getDist(path[path.size()-2]->getId(),path[path.size()-1]->getId());
}

