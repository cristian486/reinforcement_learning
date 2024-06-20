#include "LearningUtils.h"


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
    unsigned int OldRow = 0, OldColumn = 0;

    for(int i = 0; i < MAX_ITERATIONS; i++) {
        printf("Running the learning algorithm. Itearion %d of %d\n", i, MAX_ITERATIONS);
        while(PlayerNode->x != ExitNode->x || PlayerNode->y != ExitNode->y) {
            OldRow = PlayerNode->x;
            OldColumn = PlayerNode->y;

            Movement MoveToMake = ChooseMovement(QLearningMatrix, PlayerNode->x, PlayerNode->y);

            MovementPlayer(MoveToMake, PlayerNode);

            double CurrentReward = GetCurrentReward(NodeArray, PlayerNode->x, PlayerNode->y);
            
            double MaxValueReward = GetMaxValueFromActions(QLearningMatrix, PlayerNode->x, PlayerNode->x);

            double BellmanEquation = CurrentReward + (GAMMA * MaxValueReward);
            double TemporalDifferenceError = BellmanEquation - QLearningMatrix[OldRow][OldColumn][MoveToMake];
            double UpdateRuleValue = QLearningMatrix[OldRow][OldColumn][MoveToMake] + (ALPHA * TemporalDifferenceError);
            QLearningMatrix[OldRow][OldColumn][MoveToMake] = UpdateRuleValue;
        }
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
    double Points = -1.0;

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
    while(PlayerNode->x != ExitNode->x || PlayerNode->y != ExitNode->y) {
        PrintMatrix(NodeArray);
        sleep(1);
        system(CLEAR_COMMAND);
        Movement MoveToMake = ChooseBetterMovement(QLearningMatrix, PlayerNode->x, PlayerNode->y);
        MovementPlayer(MoveToMake, PlayerNode);
        VerifyIfIsOverlapping(NodeArray, PlayerNode->x, PlayerNode->y);
    }
    ResetNodeArray(NodeArray);
}