
#include <cstdlib>
#include <iostream>
#include "Controller.h"

void Controller::clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    // Assume POSIX
        std::system("clear");
#endif
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
                    //readGraph();
                    mainMenu();
                    break;
                case 2:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    //readGraph();
                    mainMenu();
                    break;
                case 3:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    //readGraph();
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
                    //readGraph();
                    mainMenu();
                    break;
                case 2:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    //readGraph();
                    mainMenu();
                    break;
                case 3:
                    clearScreen();
                    std::cout << "\nLoading Data...\n";
                    //readGraph();
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
    std::cout << "1. Brute Force/Backtracking\n";
    std::cout << "2. Triangular Approximation Heuristic\n";
    std::cout << "3. Other Heuristic\n";
    std::cout << "0. Exit\n";
    std::cout << "Option: ";
    int option;
    std::string aux;
    std::cin >> option;
    switch (option) {
        case 1:
            //brute_force();
            break;
        case 2:
            //triangular();
            break;
        case 3:
            //algoritmo_dos_deuses();
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

