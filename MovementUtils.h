#ifndef MOVEMENTUTILS_H
#define MOVEMENTUTILS_H

    #include "NodeUtils.h"
    #include <stdlib.h>

    #define NUMBER_OF_MOVEMENTS 4

    typedef enum {
        UP  = 0,
        DOWN = 1,
        LEFT = 2,
        RIGHT = 3,
    } Movement; 

    void MovementPlayer(Movement Move, Node * PlayerNode);
    Movement ChooseRandomMovement(unsigned int CoordinateX, unsigned int CoordinateY);
    int IsMovementValid(Movement Move, unsigned int CoordinateX, unsigned int CoordinateY);
    Movement ChooseMovement(double QLearningMatrix[MAX_SIZE][MAX_SIZE][NUMBER_OF_MOVEMENTS], unsigned int CoordinateX, unsigned int CoordinateY);
    Movement ChooseBetterMovement(double QLearningMatrix[MAX_SIZE][MAX_SIZE][NUMBER_OF_MOVEMENTS], unsigned int CoordinateX, unsigned int CoordinateY);
#endif