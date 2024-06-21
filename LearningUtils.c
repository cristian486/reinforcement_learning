#include "LearningUtils.h"

double EXPLORATION_RATE = MAX_EXPLORATION_RATE;

void InitializeLearningMatrix(double QLearningMatrix[MAX_SIZE][MAX_SIZE][NUMBER_OF_MOVEMENTS]) {
    for(int i = 0; i < MAX_SIZE; i++) {
        for(int j = 0; j < MAX_SIZE; j++) {
            for(int m = 0; m < NUMBER_OF_MOVEMENTS; m++) {
                QLearningMatrix[i][j][m] = 0.0;
            }
        }
    }
}

void RunLearningAlgorithm(double QLearningMatrix[MAX_SIZE][MAX_SIZE][NUMBER_OF_MOVEMENTS], Node * NodeArray[], Node * PlayerNode, Node * ExitNode) {
    EXPLORATION_RATE = MAX_EXPLORATION_RATE;
    unsigned int OldRow = 0, OldColumn = 0;

    for(int episode = 0; episode < MAX_ITERATIONS; episode++) {

        printf("Executando o algoritmo de aprendizado. Iteração %d de %d - EXPLORATION_RATE: %.2f\n", (episode + 1), MAX_ITERATIONS, EXPLORATION_RATE);


        for(int step = 0; step < MAX_STEPS_PER_EPISODE; step++) {
            OldRow = PlayerNode->x;
            OldColumn = PlayerNode->y;

            Movement MoveToMake = ChooseMovement(QLearningMatrix, PlayerNode->x, PlayerNode->y, EXPLORATION_RATE);

            MovementPlayer(MoveToMake, PlayerNode);

            double CurrentReward = GetCurrentReward(NodeArray, PlayerNode->x, PlayerNode->y);
            
            double MaxValueReward = GetMaxValueFromActions(QLearningMatrix, PlayerNode->x, PlayerNode->x);

            QLearningMatrix[OldRow][OldColumn][MoveToMake] = QLearningMatrix[OldRow][OldColumn][MoveToMake] + ALPHA * (CurrentReward + GAMMA * MaxValueReward - QLearningMatrix[OldRow][OldColumn][MoveToMake]);

            if(PlayerHaveFinished(NodeArray, PlayerNode->x, PlayerNode->y))
                break;
        }


        EXPLORATION_RATE = MIN_EXPLORATION_RATE + (MAX_EXPLORATION_RATE - MIN_EXPLORATION_RATE) * exp(-EXPLORATION_RATE_DECAY * episode);

        ResetNodeArray(NodeArray);
    }
}


double GetMaxValueFromActions(double QLearningMatrix[MAX_SIZE][MAX_SIZE][NUMBER_OF_MOVEMENTS], unsigned int CoordinateX, unsigned int CoordinateY) {
    double MaxValue = 0.0;

    for(int i = 0; i < NUMBER_OF_MOVEMENTS; i++) {
        if(QLearningMatrix[CoordinateX][CoordinateY][i] > MaxValue)
                MaxValue = QLearningMatrix[CoordinateX][CoordinateY][i];
    }

    return MaxValue;
}


double GetCurrentReward(Node * NodeArray[], unsigned int CoordinateX, unsigned int CoordinateY) {
    double Points = 0.0;

    for(int i = 1; i < MAX_NODE_ARRAY_SIZE; i++) {

        Node * CurrentNode = NodeArray[i];
        
        if(CurrentNode != NULL && CurrentNode->x == CoordinateX && CurrentNode->y == CoordinateY && NodeArray[i]->active) {
            NodeArray[i]->active = 0;
            Points = CurrentNode->points;
            break;
        }

    }

    return Points;
}

void RunBasedOnKnowledge(double QLearningMatrix[MAX_SIZE][MAX_SIZE][NUMBER_OF_MOVEMENTS], Node * NodeArray[], Node * PlayerNode, Node * ExitNode) { 
    int Step = 0;
    while(PlayerNode->x != ExitNode->x || PlayerNode->y != ExitNode->y) {
        Step++;
        PrintMatrix(NodeArray);
        sleep(1);
        system(CLEAR_COMMAND);
        Movement MoveToMake = ChooseBetterMovement(QLearningMatrix, PlayerNode->x, PlayerNode->y);
        MovementPlayer(MoveToMake, PlayerNode);
        VerifyIfIsOverlapping(NodeArray, PlayerNode->x, PlayerNode->y);
        if(Step == MAX_STEPS_PER_EPISODE)
            break;
    }
    ResetNodeArray(NodeArray);
}

int PlayerHaveFinished(Node * NodeArray[], unsigned int CoordinateX, unsigned int CoordinateY) {
    for(int i = 1; i < MAX_NODE_ARRAY_SIZE; i++)
        if(NodeArray[i]->x == CoordinateX && NodeArray[i]->y == CoordinateY && (NodeArray[i]->letter == ZOMBIE_LETTER || NodeArray[i]->letter == TRAP_LETTER || NodeArray[i]->letter == EXIT_LETTER))
            return 1;

    return 0;
}