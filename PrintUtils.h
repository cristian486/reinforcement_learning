#ifndef PRINTUTILS_H
#define PRINTUTILS_H
    
    #include <stdio.h>
    #ifdef _WIN32
        #include <windows.h>
        #define CLEAR_COMMAND "cls"
    #elif defined(__linux__) || defined(__APPLE__)
        #include <unistd.h>
        #define CLEAR_COMMAND "clear"
    #endif
    #include "NodeUtils.h"
    #include "MovementUtils.h"


    unsigned char ShowMenu();
    void PrintMatrix(Node * NodeArray[]);
    void PrintQLearningMatrix(double QLearningMatrix[MAX_SIZE][MAX_SIZE][NUMBER_OF_MOVEMENTS]);
#endif