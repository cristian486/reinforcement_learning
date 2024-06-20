#include "NodeUtils.h"

void InitializeNodeArray(Node * NodeArray[], Node ** PlayerNode, Node ** ExitNode, unsigned int * MemoryReservationError, unsigned int MaxSize){
    for(int i = 0; i < MAX_NODE_ARRAY_SIZE; i++)
        NodeArray[i] = NULL;

    for(int i = 0; i < MAX_NODE_ARRAY_SIZE; i++) {
        NodeArray[i] = (Node *) calloc(1, sizeof(Node));

        if(NodeArray[i] == NULL) {
            *MemoryReservationError = 1;
            break;
        }

        if(i == 0) 
            InitializeNode(NodeArray, PLAYER, i, MaxSize);
        else if((i + 1) == MAX_NODE_ARRAY_SIZE)
            InitializeNode(NodeArray, EXIT, i, MaxSize);
        else {
            NodeType Type = rand() % 3 + 1;
            InitializeNode(NodeArray, Type, i, MaxSize);
        }
    }

    *PlayerNode = NodeArray[0];
    *ExitNode = NodeArray[MAX_NODE_ARRAY_SIZE - 1];

    QuickSort(NodeArray, 0, MAX_NODE_ARRAY_SIZE - 1);       
}

void InitializeNode(Node * NodeArray[], NodeType Type, unsigned int IndexOfNodeToInitialize, unsigned int MaxSize) {
    Node * node = NodeArray[IndexOfNodeToInitialize];
    switch (Type) {
        case PLAYER:
            node->x = 0;
            node->y = 0;
            node->letter = PLAYER_LETTER;
            node->active = 1;
            node->backgroud_color = "\033[42m";
            break;
        case ZOMBIE:
            GenerateNodePosition(NodeArray, node, MaxSize);
            node->letter = ZOMBIE_LETTER;
            node->active = 1;
            node->backgroud_color = "\033[41m";
            node->points = -10.0;
            break;
        case SUPPLY:
            GenerateNodePosition(NodeArray, node, MaxSize);
            node->letter = SUPPLY_LETTER;
            node->active = 1;
            node->backgroud_color = "\033[44m";
            node->points = 10.0;
            break;
        case TRAP:
            GenerateNodePosition(NodeArray, node, MaxSize);
            node->letter = TRAP_LETTER;
            node->active = 1;
            node->backgroud_color = "\x1b[48;5;244m";
            node->points = -10.0;
            break;
        case EXIT:
            node->x = MaxSize - 1;
            node->y = MaxSize - 1;
            node->letter = 'X';
            node->points = 100.0;
            node->backgroud_color = "\033[47m";
            node->active = 1;
            break;
    }
}

void GenerateNodePosition(Node * NodeArray[], Node * Node, unsigned int MaxSize) {
        unsigned int RandomX = rand() % ((MaxSize - 2) + 1 - 1) + 1;
        unsigned int RandomY = rand() % ((MaxSize - 2) + 1 - 1) + 1;

        while(IsPositionOccupiedByNode(NodeArray, RandomX, RandomY) != NULL) {
                RandomX = rand() % ((MaxSize - 1) + 1 - 1) + 1;
                RandomY = rand() % ((MaxSize - 1) + 1 - 1) + 1;
        }
    
        Node->x = RandomX;
        Node->y = RandomY;
}

Node * IsPositionOccupiedByNode(Node * NodeArray[], unsigned int CoordinateX, unsigned int CoordinateY) {
    for(int i = 0; i < MAX_NODE_ARRAY_SIZE; i++)
        if(NodeArray[i] != NULL && NodeArray[i]->x == CoordinateX && NodeArray[i]->y == CoordinateY)
            return NodeArray[i];

    return NULL;
}


void VerifyIfIsOverlapping(Node * NodeArray[], unsigned int CoordinateX, unsigned int CoordinateY) {
    for(int i = 1; i < MAX_NODE_ARRAY_SIZE; i++)
        if(NodeArray[i] != NULL && NodeArray[i]->x == CoordinateX && NodeArray[i]->y == CoordinateY) {
            NodeArray[i]->active = 0;
            break;
        }        
}


void FreeNodeArray(Node * NodeArray[]) {
    printf("Freeing the Nodes allocated!\n");
    for(int i = 0; i < MAX_NODE_ARRAY_SIZE; i++) {
        if(NodeArray[i]) {
            free(NodeArray[i]);
            NodeArray[i] = NULL;
        }
    }
}


void ResetNodeArray(Node * NodeArray[]) {
    NodeArray[0]->x = 0;
    NodeArray[0]->y = 0;
    for(int i = 0; i < MAX_NODE_ARRAY_SIZE; i++)
        NodeArray[i]->active = 1;
}