#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <queue>
#include <algorithm>
#include "Controller.h"

void Controller::clearScreen() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

void Controller::dataReset() {
    clearScreen();
    std::cout << "Clearing data...\n";
    for (auto & vertice : vertices) {
        vertice.second -> clear();
        delete vertice.second;
    }
    vertices.clear();
    graph.clear();
    graph = Graph();
    distances.clear();
}

std::vector<std::vector<double>> Controller::createDistanceMatrix() {
    const std::vector<Vertex*>& vertexSet = graph.getVertexSet();
    auto numVertices = vertexSet.size();

    std::vector<std::vector<double>> distanceMatrix(numVertices, std::vector<double>(numVertices, 0.0));

    for (int i = 0; i < numVertices; i++) {
        for (int j = i + 1; j < numVertices; j++) {
            unsigned int id1 = vertexSet[i]->getId();
            unsigned int id2 = vertexSet[j]->getId();

            double distance = graph.getDist(id1, id2);

            distanceMatrix[i][j] = distance;
            distanceMatrix[j][i] = distance;
        }
    }

    return distanceMatrix;
}

void Controller::readRealWorldGraph(const std::string& nodes, const std::string& edges) {
    std::ifstream ifsN(nodes);

    if(!ifsN.is_open()){
        std::cout << "ERROR: File not found.\n";
        exit(1);
    }

    std::string line;
    int id;
    double lat,lon;
    int vertexCounter = 0;

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
            vertexCounter++;
        }

    }
    ifsN.close();

    std::ifstream ifsE(edges);
    if(!ifsE.is_open()){
        std::cout << "ERROR: File not found.\n";
        exit(1);
    }

    std::getline(ifsE, line);

    int idOrig,idDest;
    double weight;
    int edgeCounter = 0;

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
        auto orig = vertices.find(idOrig)->second;
        auto dest = vertices.find(idDest)->second;
        graph.addEdge(orig,dest,weight);
        edgeCounter++;
    }
    ifsE.close();
    graph.setHasCoords(true);
    if (edgeCounter == vertexCounter * (vertexCounter - 1) / 2)
        graph.setFullyConnected(true);

    distances = createDistanceMatrix();
}

void Controller::readToyGraph(const std::string& edges) {
    std::ifstream ifs(edges);

    if(!ifs.is_open()){
        std::cout << "ERROR: File not found.\n";
        exit(1);
    }

    std::string line;
    getline(ifs, line);

    int idOrig, idDest;
    double weight;

    int edgeCounter = 0;
    int vertexCounter = 0;

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
            vertexCounter++;
        }
        if(vertices.find(idDest) == vertices.end()){
            auto v = new Vertex(idDest);
            vertices.insert(std::make_pair(idDest, v));
            graph.addVertex(v);
            vertexCounter++;
        }
        auto orig = vertices.find(idOrig)->second;
        auto dest = vertices.find(idDest)->second;
        graph.addEdge(orig,dest, weight);
        edgeCounter++;
    }
    ifs.close();
    if (edgeCounter == vertexCounter * (vertexCounter - 1) / 2)
        graph.setFullyConnected(true);

    distances = createDistanceMatrix();
}

void Controller::readFullyConGraph(const std::string& edges) {
    std::ifstream ifs(edges);

    if(!ifs.is_open()){
        std::cout << "ERROR: File not found.\n";
        exit(1);
    }

    std::string line;
    int idOrig, idDest;
    double weight;

    int edgeCounter = 0;
    int vertexCounter = 0;

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
            vertexCounter++;
        }
        if(vertices.find(idDest)==vertices.end()){
            auto v = new Vertex(idDest);
            vertices.insert(std::make_pair(idDest,v));
            graph.addVertex(v);
            vertexCounter++;
        }
        auto orig = vertices.find(idOrig)->second;
        auto dest = vertices.find(idDest)->second;
        graph.addEdge(orig,dest,weight);
        edgeCounter++;
    }
    ifs.close();
    if (edgeCounter == vertexCounter * (vertexCounter - 1) / 2)
        graph.setFullyConnected(true);

    distances = createDistanceMatrix();
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

    int option, option2, option3;
    clock_t begin;
    std::string aux;
    std::cin >> option;
    std::string filename;
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
                    readRealWorldGraph("../../Project2Graphs/Real-World-Graphs/graph1/nodes.csv","../../Project2Graphs/Real-World-Graphs/graph1/edges.csv");
                    mainMenu();
                    break;
                case 2:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readRealWorldGraph("../../Project2Graphs/Real-World-Graphs/graph2/nodes.csv","../../Project2Graphs/Real-World-Graphs/graph2/edges.csv");
                    mainMenu();
                    break;
                case 3:
                    clearScreen();
                    begin = clock();
                    std::cout << "\nLoading Data...\n";
                    readRealWorldGraph("../../Project2Graphs/Real-World-Graphs/graph3/nodes.csv","../../Project2Graphs/Real-World-Graphs/graph3/edges.csv");
                    mainMenu();
                    break;
                case 0:
                    startMenu();
                    break;
                default:
                    std::cout << "ERROR: Invalid option.\n";
                    std::cout << "(Press any key to continue)\n";
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
                    readToyGraph("../../Project2Graphs/Toy-Graphs/shipping.csv");
                    mainMenu();
                    break;
                case 2:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readToyGraph("../../Project2Graphs/Toy-Graphs/stadiums.csv");
                    mainMenu();
                    break;
                case 3:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readToyGraph("../../Project2Graphs/Toy-Graphs/tourism.csv");
                    mainMenu();
                    break;
                case 0:
                    startMenu();
                    break;
                default:
                    std::cout << "ERROR: Invalid option.\n";
                    std::cout << "(Press any key to continue)\n";
                    std::cin >> aux;
                    startMenu();
                    break;
            }
            break;
        case 3:
            clearScreen();
            std::cout << "/t**Start Menu**\n\n";
            std::cout << "Select a Fully Connected Graph:\n";
            std::cout << "1. With 25 nodes\n";
            std::cout << "2. With 50 nodes\n";
            std::cout << "3. With 75 nodes\n";
            std::cout << "4. With 100 nodes\n";
            std::cout << "5. With 200 nodes\n";
            std::cout << "6. With 300 nodes\n";
            std::cout << "7. With 400 nodes\n";
            std::cout << "8. With 500 nodes\n";
            std::cout << "9. With 600 nodes\n";
            std::cout << "10. With 700 nodes\n";
            std::cout << "11. With 800 nodes\n";
            std::cout << "12. With 900 nodes\n";
            std::cout << "0. Go Back\n";
            std::cout << "Option: ";
            std::cin >> option3;
            switch (option3) {
                case 1:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readFullyConGraph("../../Project2Graphs/Extra_Fully_Connected_Graphs/edges_25.csv");
                    mainMenu();
                    break;
                case 2:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readFullyConGraph("../../Project2Graphs/Extra_Fully_Connected_Graphs/edges_50.csv");
                    mainMenu();
                    break;
                case 3:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readFullyConGraph("../../Project2Graphs/Extra_Fully_Connected_Graphs/edges_75.csv");
                    mainMenu();
                    break;
                case 4:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readFullyConGraph("../../Project2Graphs/Extra_Fully_Connected_Graphs/edges_100.csv");
                    mainMenu();
                    break;
                case 5:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readFullyConGraph("../../Project2Graphs/Extra_Fully_Connected_Graphs/edges_200.csv");
                    mainMenu();
                    break;
                case 6:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readFullyConGraph("../../Project2Graphs/Extra_Fully_Connected_Graphs/edges_300.csv");
                    mainMenu();
                    break;
                case 7:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readFullyConGraph("../../Project2Graphs/Extra_Fully_Connected_Graphs/edges_400.csv");
                    mainMenu();
                    break;
                case 8:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readFullyConGraph("../../Project2Graphs/Extra_Fully_Connected_Graphs/edges_500.csv");
                    mainMenu();
                    break;
                case 9:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readFullyConGraph("../../Project2Graphs/Extra_Fully_Connected_Graphs/edges_600.csv");
                    mainMenu();
                    break;
                case 10:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readFullyConGraph("../../Project2Graphs/Extra_Fully_Connected_Graphs/edges_700.csv");
                    mainMenu();
                    break;
                case 11:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readFullyConGraph("../../Project2Graphs/Extra_Fully_Connected_Graphs/edges_800.csv");
                    mainMenu();
                    break;
                case 12:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    readFullyConGraph("../../Project2Graphs/Extra_Fully_Connected_Graphs/edges_900.csv");
                    mainMenu();
                    break;
                case 0:
                    startMenu();
                    break;
                default:
                    std::cout << "ERROR: Invalid option.\n";
                    std::cout << "(Press any key to continue)\n";
                    std::cin >> aux;
                    startMenu();
                    break;
            }
            break;
        case 4:
            clearScreen();
            std::cout << "/t**Start Menu**\n\n";
            std::cout << "What is the path to the file containing the graph you want to use?\n";
            std::cout << "(Note that the file should be in the folder Project2Graphs)\n";
            std::cout << "Filename: ";
            std::cin >> filename;
            clearScreen();
            std::cout << "\nLoading Data...\n";
            filename = "../../Project2Graphs/" + filename;
            readToyGraph(filename);
            mainMenu();
            break;
        case 0:
            break;
        default:
            std::cout << "ERROR: Invalid option.\n";
            break;
    }
}

void Controller::mainMenu() {
    clearScreen();

    std::cout << "\t**Traveling Salesperson Problem**\n\n";
    std::cout << "How would you like to calculate the best solution to the TSP in the graph you selected?\n";
    std::cout << "1. Backtracking\n";
    std::cout << "2. Triangular Approximation heuristic\n";
    std::cout << "3. Lin-Kernighan algorithm\n";
    std::cout << "4. Change graph\n";
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
            std::cout << "Calculating best solution using a Triangular Approximation heuristic...\n";
            triangular();
            break;
        case 3:
            clearScreen();
            std::cout << "Calculating best solution using Lin-Kernighan's algorithm...\n";
            LK();
            break;
        case 4:
            dataReset();
            startMenu();
            break;
        case 0:
            break;
        default:
            std::cout << "ERROR: Invalid option.\n";
            std::cout << "(Press any key to continue)\n";
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
        auto adj = current->getAdj();
        for(const auto& edge : adj){
            if (edge->getDest() == graph.getVertexSet()[0]) {
                distance += edge->getWeight();
                path.push_back(graph.getVertexSet()[0]);

                if(distance < bestDistance){
                    bestDistance = distance;
                    bestPath = path;
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
    auto vertexSet = graph.getVertexSet();

    for (const auto& vertex : vertexSet) {
        vertex->setVisited(false);
    }

    backtrackingAux(const_cast<Vertex *&>(graph.getVertexSet()[0]), path, distance, bestDistance, bestPath);

    clock_t end = clock();
    clearScreen();
    std::cout << "\t**Traveling Salesperson Problem**\n\n";

    if(bestPath.size() != (vertices.size() + 1)){
        std::cout << "No path was found using the Backtracking approach!\n";
        std::cout << "Time taken to calculate: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds.\n";
        std::cout << "(Press any key to continue)\n";
        std::string aux;
        std::cin >> aux;
        mainMenu();
    }
    std::cout << "Calculated path: ";
    std::cout << bestPath[0]->getId();

    for (int i = 1; i < bestPath.size(); ++i) {
        std::cout << " -> " << bestPath[i]->getId();
    }

    std::cout << "\nMinimum distance calculated using the Backtracking approach: " << bestDistance << "\n";
    std::cout << "Time taken to calculate: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds.\n";
    std::cout << "(Press any key to continue)\n";
    std::string aux;
    std::cin >> aux;
    mainMenu();
}

double Controller::calculateDistance(std::vector<Vertex*> &path) {
    double distance=0;
    int pathSize = path.size()-1;
    for(int i = 0; i < pathSize ; i++) {
        int id1 = path[i]->getId();
        int id2 = path[i + 1]->getId();
        distance += distances[id1][id2];
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
                    if(graph.usesCoords()){
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

    if(path.size() != (vertices.size() + 1)){
        std::cout << "No path was found using the Triangular Approximation heuristic!\n";
        std::cout << "Time taken to calculate: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds.\n";
        std::cout << "(Press any key to continue)\n";
        std::string aux;
        std::cin >> aux;
        mainMenu();
        return;
    }

    double distance = calculateDistance(path);
    std::cout << "\t**Traveling Salesperson Problem**\n\n";
    if (distance >= 1000) std::cout << "\nMinimum distance calculated using the Triangular Approximation heuristic: " << distance / 1000 << " kilometers.\n";
    else std::cout << "\nMinimum distance calculated using the Triangular Approximation heuristic: " << distance << " meters.\n";
    std::cout << "Time taken to calculate: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds.\n";
    std::cout << "(Press any key to continue)\n";
    std::string aux;
    std::cin >> aux;
    mainMenu();
}

void Controller::nearestNeighborGreedy(std::vector<Vertex*> &path, double &distance) {
    auto vertexSet = graph.getVertexSet();
    auto vertexSetSize = vertexSet.size();
    bool flag = true;
    Vertex* current = vertexSet[0];
    current->setVisited(true);
    path.push_back(current);

    while(path.size() < vertexSetSize && flag) {
        std::priority_queue<Edge*, std::vector<Edge*>, EdgeComparator> pq(current -> getAdj().begin(), current -> getAdj().end());
        flag = false;
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
                flag = true;
                break;
            }
        }
    }
    path.push_back(graph.getVertexSet()[0]);

    distance += distances[path[path.size()-2]->getId()][path[path.size()-1]->getId()];
}

void Controller::linKernighan(std::vector<Vertex*>& path, double& distance) {
    std::vector<Vertex*>& bestPath = path;
    double bestDistance = distance;
    bool improved = true;
    auto pathSize = bestPath.size();

    while (improved) {
        improved = false;
        for (int i = 0; i < pathSize - 2; ++i) {
            for (int j = i + 1; j < pathSize - 1; ++j) {
                std::vector<Vertex*> newPath = bestPath;
                reverseSubpath(newPath, i + 1, j);
                double newDistance = bestDistance - distances[bestPath[i + 1]->getId()][bestPath[i]->getId()] - distances[bestPath[j + 1]->getId()][bestPath[j]->getId()] + distances[newPath[i + 1]->getId()][newPath[i]->getId()] + distances[newPath[j + 1]->getId()][newPath[j]->getId()];

                if (newDistance < bestDistance) {
                    bestPath = newPath;
                    bestDistance = newDistance;
                    improved = true;
                }
            }
        }

    }
    path = bestPath;
    distance = bestDistance;
}

void Controller::reverseSubpath(std::vector<Vertex*>& path, int start, int end) {
    while (start < end) {
        std::swap(path[start], path[end]);
        ++start;
        --end;
    }
}

void Controller::LK() {
    clearScreen();
    std::cout << "\t**Traveling Salesperson Problem**\n\n";
    clock_t start = clock();
    std::vector<Vertex*> path;

    for (const auto& vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
    }

    double distance = 0;
    nearestNeighborGreedy(path, distance);
    if (path.size() != (vertices.size() + 1)) {
        std::cout << "No path was found using the Nearest Neighbor approach!\n";
        std::cout << "Time taken to calculate: " << (double)(clock()-start)/CLOCKS_PER_SEC << " seconds.\n";
        std::cout << "(Press any key to continue)\n";
        std::string aux;
        std::cin >> aux;
        mainMenu();
        return;
    }

    if (distance >= 1000) std::cout << "Distance calculated using the Nearest Neighbor approach: " << distance / 1000 << " kilometers.\n";
    else std::cout << "Distance calculated using the Nearest Neighbor approach: " << distance << " meters.\n";
    std::cout << "Time taken to calculate: " << (double)(clock()-start)/CLOCKS_PER_SEC << " seconds.\n";

    clock_t start1 = clock();
    linKernighan(path, distance);

    if (distance >= 1000) std::cout << "Distance after applying the Lin-Kernighan algorithm: " << distance / 1000 << " kilometers.\n";
    else std::cout << "Distance after applying the Lin-Kernighan algorithm: " << distance << " meters.\n";

    std::cout << "Time taken to calculate: " << (double)(clock()-start1)/CLOCKS_PER_SEC << " seconds.\n";
    std::cout << "(Press any key to continue)\n";
    std::string aux;
    std::cin >> aux;

    mainMenu();
}

