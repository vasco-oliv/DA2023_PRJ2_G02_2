//
// Created by 35191 on 28/04/2023.
//

#include <cstdlib>
#include "Controller.h"

void clearScreen() {
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
}