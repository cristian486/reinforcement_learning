#include "PrintUtils.h"


unsigned char ShowMenu() {
	unsigned char Input = '\0';
	printf("  .88888.   dP                                            oo                   \n"); 
	printf(" d8'   `8b  88                                                                 \n"); 
	printf(" 88     88  88        .d8888b. .d8888b. 88d888b. 88d888b. dP 88d888b. .d8888b. \n"); 
	printf(" 88  db 88  88        88ooood8 88'  `88 88'  `88 88'  `88 88 88'  `88 88'  `88 \n"); 
	printf(" Y8.  Y88P  88        88.  ... 88.  .88 88       88    88 88 88    88 88.  .88 \n"); 
	printf("  `8888PY8b 88888888P `88888P' `88888P8 dP       dP    dP dP dP    dP `8888P88 \n"); 
	printf("                                                                           .88 \n"); 
	printf("                                                                       d8888P  \n");
	printf("\n\tOpções:\n");
	printf("\t\t1 - Mostrar a matrix\n");
	printf("\t\t2 - Mostrar a matrix de aprendizado\n");
	printf("\t\t3 - Treinar o algoritmo\n");
	printf("\t\t4 - Percorrer o labirinto com base no conhecimento\n");
	printf("\t\t5 - Sair\n\t\t");
	scanf(" %c", &Input);
	return Input;
}


void PrintQLearningMatrix(double QLearningMatrix[MAX_SIZE][MAX_SIZE][NUMBER_OF_MOVEMENTS]) {
	for(int i = 0; i < MAX_SIZE; i++) {
        for(int j = 0; j < MAX_SIZE; j++) {
			printf("Linha %d Coluna %d:\t", i, j);
            for(int m = 0; m < NUMBER_OF_MOVEMENTS; m++) {
				printf("%02.4f\t", QLearningMatrix[i][j][m]);
            }
			printf("\n");
        }
    }
}


void PrintMatrix(Node * NodeArray[]) {
	printf("    ");
	for(int i = 0; i < MAX_SIZE; i++)
		printf("%02d ", i);

	printf("\t\t\tP = PLAYER\tZ = ZOMBIE\tT = TRAP\tS = SUPPLY\n");

	for(int i = 0; i < MAX_SIZE; i++) {
		if(i < 10) printf("%02d  ", i); else printf("%d  ", i);

		for(int j = 0; j < MAX_SIZE; j++) {
			Node * CurrentNode = IsPositionOccupiedByNode(NodeArray, i, j);
			
			if(CurrentNode != NULL && CurrentNode->active) {
				printf("%s", CurrentNode->backgroud_color);
				printf("%c ", CurrentNode->letter);
				printf("\033[0m");
				printf(" ");
			} else
				printf(".  ");
		}

		printf("\n");
	}
}
