#include "MovementUtils.h"

double EXPLORATION_RATE = 0.9;

void MovementPlayer(Movement Move, Node * PlayerNode) {
    switch(Move) {
        case UP:
            PlayerNode->x -= 1;
            break;
        case DOWN:
            PlayerNode->x += 1;
            break;
        case LEFT:
            PlayerNode->y -= 1;
            break;
        case RIGHT:
            PlayerNode->y += 1;
            break;
    }
}

int IsMovementValid(Movement Move, unsigned int CoordinateX, unsigned int CoordinateY) {
    if(Move == UP && CoordinateX > 0 && (CoordinateX - 1) > -1)
        return 1;
    
    if(Move == DOWN && CoordinateX < MAX_SIZE && (CoordinateX + 1) < MAX_SIZE)
        return 1;
    
    if(Move == LEFT && CoordinateY > 0 && (CoordinateY - 1) > -1)
        return 1;
    
    if(Move == RIGHT && CoordinateY < MAX_SIZE && (CoordinateY + 1) < MAX_SIZE)
        return 1;

    return 0;
}

Movement ChooseRandomMovement(unsigned int CoordinateX, unsigned int CoordinateY) {
    Movement RandomMove = (Movement) rand() % 4;

    while (!IsMovementValid(RandomMove, CoordinateX, CoordinateY)) {
        RandomMove = (Movement) rand() % 4;
    }

    return RandomMove;
}

Movement ChooseBetterMovement(double QLearningMatrix[MAX_SIZE][MAX_SIZE][NUMBER_OF_MOVEMENTS], unsigned int CoordinateX, unsigned int CoordinateY) {
    double MaxValue = -1.0;
    unsigned int BetterMovementIndex = 0;

    for(int i = 0; i < NUMBER_OF_MOVEMENTS; i++) {

        if(QLearningMatrix[CoordinateX][CoordinateY][i] >= MaxValue && IsMovementValid((Movement) i, CoordinateX, CoordinateY)) {
            BetterMovementIndex = i;
            MaxValue = QLearningMatrix[CoordinateX][CoordinateY][i];
        }
    }

    return (Movement) BetterMovementIndex;
}

Movement ChooseMovement(double QLearningMatrix[MAX_SIZE][MAX_SIZE][NUMBER_OF_MOVEMENTS], unsigned int CoordinateX, unsigned int CoordinateY) {
    double RandomNumber = rand() / (double) RAND_MAX;

    if(RandomNumber < EXPLORATION_RATE)
        return ChooseRandomMovement(CoordinateX, CoordinateY);
    
    if((EXPLORATION_RATE - 0.01) > 0.1)
        EXPLORATION_RATE -= 0.01;

    return ChooseBetterMovement(QLearningMatrix,CoordinateX, CoordinateY);
}