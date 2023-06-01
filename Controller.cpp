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
        iss >> lon;
        iss.ignore(1);
        iss >> lat;

        if(vertices.find(id)==vertices.end()){
            auto v = new Vertex(id,lat,lon);
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

void Controller::readToyGraph(const std::string& edges) {
    std::ifstream ifs(edges);

    if(!ifs.is_open()){
        std::cout << "ERROR: File not found\n";
        exit(1);
    }

    std::string line;
    getline(ifs, line);

    int idOrig, idDest;
    double weight;

    while(std::getline(ifs,line)){
        std::istringstream iss(line);
        iss >> idOrig;
        iss.ignore(1);
        iss >> idDest;
        iss.ignore(1);
        iss >> weight;

        if(vertices.find(idOrig) == vertices.end()){
            auto v = new Vertex(idOrig);
            vertices.insert(std::make_pair(idOrig, v));
            graph.addVertex(v);
        }
        if(vertices.find(idDest) == vertices.end()){
            auto v = new Vertex(idDest);
            vertices.insert(std::make_pair(idDest, v));
            graph.addVertex(v);
        }
        graph.addEdge(idOrig,idDest,weight);
    }
}

void Controller::readFullyConGraph(const std::string& edges) {
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
            auto v = new Vertex(idOrig);
            vertices.insert(std::make_pair(idOrig,v));
            graph.addVertex(v);
        }
        if(vertices.find(idDest)==vertices.end()){
            auto v = new Vertex(idDest);
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
    clock_t begin;
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
                    begin = clock();
                    std::cout << "\nLoading Data...\n";
                    readRealWorldGraph("../Project2Graphs/Real-World-Graphs/graph3/nodes.csv","../Project2Graphs/Real-World-Graphs/graph3/edges.csv");
                    std::cout << "Time elapsed: " << double(clock() - begin) / CLOCKS_PER_SEC << " seconds\n";
                    std::cout << "(Press any key to continue)";
                    std::cin >> aux;
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
            clearScreen();
            std::cout << "\nLoading Data...\n";
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
            clearScreen();
            std::cout << "Calculating best solution using a Triangular Approximation Heuristic...\n";
            triangular();
            break;
        case 3:
            clearScreen();
            std::cout << "Calculating best solution using God's Algorithm...\n";
            godsAlgorithm();
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

void Controller::backtrackingAux(Vertex* &current, std::vector<Vertex*>& path, double& distance, double& bestDistance, std::vector<Vertex*>& bestPath) {
    if(distance >= bestDistance) return;

    (*current).setVisited(true);
    path.push_back(current);

    if (path.size() == graph.getVertexSet().size()) {
        for(const auto& edge : current->getAdj()){
            if (edge->getDest() == graph.getVertexSet()[0]) {
                distance += edge->getWeight();
                path.push_back(graph.getVertexSet()[0]);

                if(distance < bestDistance){
                    bestDistance = distance;
                    bestPath = path;
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

    std::priority_queue<Edge*, std::vector<Edge*>, EdgeComparator> pq(current -> getAdj().begin(), current -> getAdj().end());
    while(!pq.empty()){
        auto edge = pq.top();
        pq.pop();

        Vertex* dest = edge->getDest();
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
    std::vector<Vertex*> path, bestPath;
    double distance = 0, bestDistance = std::numeric_limits<double>::max();

    for (const auto& vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
    }

    backtrackingAux(const_cast<Vertex *&>(graph.getVertexSet()[0]), path, distance, bestDistance, bestPath);

    clock_t end = clock();
    clearScreen();
    std::cout << "\t**Traveling Salesperson Problem**\n\n";

    if(bestPath.size() != (graph.getVertexSet().size()+1)){
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

double Controller::calculateDistance(std::vector<Vertex*> &path) {
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

void Controller::preorder(std::vector<Vertex*>& path, Vertex*& current) {
    path.push_back(current);
    current->setVisited(true);

    for(auto v: current->sons){
        if(!v->isVisited()){
            preorder(path, v);
        }
    }
}

void Controller::primMST() {
    for (const auto& vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
        vertex->sons.clear();
    }
    auto root = graph.getVertexSet()[0];
    root->setVisited(true);
    std::priority_queue<Edge*, std::vector<Edge*>, EdgeComparator> pq(root -> getAdj().begin(), root -> getAdj().end());

    while(!pq.empty()){
        auto edge = pq.top();
        pq.pop();
        Vertex* dest = edge->getDest();
        if (!dest->isVisited()) {
            dest->setVisited(true);
            edge->getOrig()->sons.push_back(dest);

            for(auto n2: graph.getVertexSet()){
                if(n2->isVisited())continue;
                Edge *e=graph.getEdge(dest,n2);
                if (e == nullptr) {
                    if(graph.hasCoords){
                        double w = graph.calculateDist(dest->getLatitude(),dest->getLongitude(),n2->getLatitude(),n2->getLongitude());
                        e = new Edge(dest, n2, w);
                        }
                    else {
                        continue;
                    }
                }
                pq.push(e);
            }
        }
    }
}

void Controller::triangular() {
    clock_t start = clock();
    std::vector<Vertex *> path;

    primMST();

    for (const auto& vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
    }

    preorder(path, const_cast<Vertex *&>(graph.getVertexSet()[0]));
    path.push_back(graph.getVertexSet()[0]);
    clock_t end = clock();
    clearScreen();


    if(path.size() != (graph.getVertexSet().size() + 1)){
        std::cout << "No path found!\n";
        std::cout << "Time: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds\n";
        std::cout << "(Press any key to continue)\n";
        std::string aux;
        std::cin >> aux;
        mainMenu();
        return;
    }

    std::cout << "\t**Traveling Salesperson Problem**\n\n";
    /*std::cout << "Best Path: ";
    std::cout << path[0]->getId();

    for (int i = 1; i < path.size(); ++i) {
        std::cout << " -> " << path[i]->getId();
    }*/
    std::cout << "Path size: " << path.size() << "\n";
    std::cout << "\nBest Distance: " << calculateDistance(path) << "\n";
    std::cout << "Time: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds\n";
    std::cout << "(Press any key to continue)\n";
    std::string aux;
    std::cin >> aux;
    mainMenu();
}

void Controller::nearestNeighborGreedy(std::vector<Vertex*> &path, double &distance) {
    Vertex* current = graph.getVertexSet()[0];
    current->setVisited(true);
    path.push_back(current);

    while(path.size() < graph.getVertexSet().size()){
        std::priority_queue<Edge*, std::vector<Edge*>, EdgeComparator> pq(current -> getAdj().begin(), current -> getAdj().end());
        while(!pq.empty()){
            auto edge = pq.top();
            pq.pop();

            Vertex* dest = edge->getDest();
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

void Controller::godsAlgorithm() {
    clearScreen();
    std::cout << "\t**Traveling Salesperson Problem**\n\n";
    clock_t start = clock();
    std::vector<Vertex*> path;
    for (const auto& vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
    }
    double distance = 0;
    nearestNeighborGreedy(path, distance);
    std::cout << "Path Size: " << path.size() << "\n";
    std::cout << "Greedy: " << distance << "\n";
    std::cout << "Time: " << (double)(clock()-start)/CLOCKS_PER_SEC << " seconds\n";
    clock_t start1 = clock();
    linKernighan(path, distance);
    std::cout << "Path Size: " << path.size() << "\n";
    std::cout << "Lin-Kernighan: " << distance << "\n";
    std::cout << "Time: " << (double)(clock()-start1)/CLOCKS_PER_SEC << " seconds\n";
    std::cout << "(Press any key to continue)\n";
    std::string aux;
    std::cin >> aux;
    mainMenu();
}

void Controller::linKernighan(std::vector<Vertex*>& path, double& distance) {
    std::vector<Vertex*>& bestPath = path;
    double bestDistance = distance;
    bool improved = true;
    int iteration = 0;
    while (improved && iteration < MAX_ITERATIONS) {
        improved = false;
        for (int i = 0; i < bestPath.size() - 2; ++i) {
            for (int j = i + 2; j < bestPath.size() - 1; ++j) {
                std::vector<Vertex*> newPath = bestPath;
                double newDistance = bestDistance;
                reverseSubpath(newPath, i + 1, j);
                newDistance = calculateDistance(newPath);
                if (newDistance < bestDistance) {
                    std::cout << "Improved from " << bestDistance << " to " << newDistance << "\n";
                    bestPath = newPath;
                    bestDistance = newDistance;
                    improved = true;
                }
            }
        }
        iteration++;
    }
    std::cout << "Number of iterations: " << iteration << "\n";
    path = bestPath;
    distance = bestDistance;
}

void Controller::reverseSubpath(std::vector<Vertex*>& path, int start, int end) {
    while (start < end) {
        std::swap(path[start], path[end]);
        start++;
        end--;
    }
}
