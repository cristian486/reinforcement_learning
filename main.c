#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "PrintUtils.h"
#include "NodeUtils.h"
#include "LearningUtils.h"

// gcc -o ReinforcmentLearning main.c PrintUtils.c  NodeUtils.c SortUtils.c MovementUtils.c LearningUtils.c

#ifdef _WIN32
	#include <windows.h>
	#define CLEAR_COMMAND "cls"
#elif defined(__linux__) || defined(__APPLE__)
	#include <unistd.h>
	#define CLEAR_COMMAND "clear"
#endif

void HandleUserInput(unsigned char UserOption, double QLearningMatrix[MAX_SIZE][MAX_SIZE][NUMBER_OF_MOVEMENTS], Node * NodeArray[], Node * PlayerNode, Node * ExitNode);

int main(const int argc, const char * argv[]) {
	srand(time(NULL));
	system(CLEAR_COMMAND);

	unsigned char UserOption = '\0';
	unsigned int MemoryReservationError = 0;

	double QLearningMatrix[MAX_SIZE][MAX_SIZE][NUMBER_OF_MOVEMENTS];
	Node * NodeArray[MAX_NODE_ARRAY_SIZE], * PlayerNode = NULL, * ExitNode = NULL;

	InitializeLearningMatrix(QLearningMatrix);
	
	InitializeNodeArray(NodeArray, &PlayerNode, &ExitNode, &MemoryReservationError, MAX_SIZE);

	while(!MemoryReservationError && UserOption != '5') {
		UserOption = ShowMenu();
		system(CLEAR_COMMAND);
		HandleUserInput(UserOption, QLearningMatrix, NodeArray, PlayerNode, ExitNode);
		system(CLEAR_COMMAND);
	}

	FreeNodeArray(NodeArray);
	PlayerNode = NULL;
	ExitNode = NULL;
	return 0;
}

void HandleUserInput(unsigned char UserOption, double QLearningMatrix[MAX_SIZE][MAX_SIZE][NUMBER_OF_MOVEMENTS], Node * NodeArray[], Node * PlayerNode, Node * ExitNode) {
	switch (UserOption) {
		case '1':
			PrintMatrix(NodeArray);
			getchar();
			getchar();
			break;
		case '2':
			PrintQLearningMatrix(QLearningMatrix);
			getchar();
			getchar();
			break;
		case '3':
			RunLearningAlgorithm(QLearningMatrix, NodeArray, PlayerNode, ExitNode);
			break;
		case '4':
			RunBasedOnKnowledge(QLearningMatrix, NodeArray, PlayerNode, ExitNode);
			break;
		case '5':
			break;
		default:
			printf("Informação fornecida não reconhecida!\n");
			break;
	}
}