#ifndef LEARNINGUTILS_H
#define LEARNINGUTILS_H

    #include <stdio.h>
    #include <math.h>
    #include "NodeUtils.h"
    #include "PrintUtils.h"
    #include "MovementUtils.h"

    #ifdef _WIN32
        #include <windows.h>
        #define CLEAR_COMMAND "cls"
    #elif defined(__linux__) || defined(__APPLE__)
        #include <unistd.h>
        #define CLEAR_COMMAND "clear"
    #endif

    #define GAMMA 0.9
    #define ALPHA 0.1
    #define MAX_EPISODES 100000
    #define MAX_STEPS_PER_EPISODE ((MAX_SIZE * MAX_SIZE) + 10)
    #define EXPLORATION_RATE_DECAY 0.001
    #define MIN_EXPLORATION_RATE 0.2
    #define MAX_EXPLORATION_RATE 1.0

    int PlayerHaveFinished(Node * NodeArray[], unsigned int CoordinateX, unsigned int CoordinateY);
    void InitializeLearningMatrix(double QLearningMatrix[MAX_SIZE][MAX_SIZE][NUMBER_OF_MOVEMENTS]);
    double GetCurrentReward(Node * NodeArray[], unsigned int CoordinateX, unsigned int CoordinateY);
    double GetMaxValueFromActions(double QLearningMatrix[MAX_SIZE][MAX_SIZE][NUMBER_OF_MOVEMENTS], unsigned int CoordinateX, unsigned int CoordinateY);
    void RunLearningAlgorithm(double QLearningMatrix[MAX_SIZE][MAX_SIZE][NUMBER_OF_MOVEMENTS], Node * NodeArray[], Node * PlayerNode, Node * ExitNode);
    void RunBasedOnKnowledge(double QLearningMatrix[MAX_SIZE][MAX_SIZE][NUMBER_OF_MOVEMENTS], Node * NodeArray[], Node * PlayerNode, Node * ExitNode);
#endif