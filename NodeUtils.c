#include "NodeUtils.h"


void ReInitializeNodeArray(Node * NodeArray[], unsigned int MaxSize) {
    for(int i = 1; i < MAX_NODE_ARRAY_SIZE; i++) {
        if((i + 1) == MAX_NODE_ARRAY_SIZE)
            InitializeNode(NodeArray, EXIT, i, MaxSize);
        else {
            NodeType Type = rand() % 3 + 1;
            InitializeNode(NodeArray, Type, i, MaxSize);
        }
    }
    QuickSort(NodeArray, 0, MAX_NODE_ARRAY_SIZE - 1);
}

void InitializeNodeArray(Node * NodeArray[], unsigned int * MemoryReservationError, unsigned int MaxSize) {
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
    QuickSort(NodeArray, 0, MAX_NODE_ARRAY_SIZE - 1);
}

void InitializeNode(Node * NodeArray[], NodeType Type, unsigned int IndexOfNodeToInitialize, unsigned int MaxSize) {
    Node * CurrentNode = NodeArray[IndexOfNodeToInitialize];
    switch (Type) {
        case PLAYER:
            CurrentNode->x = 0;
            CurrentNode->y = 0;
            CurrentNode->letter = PLAYER_LETTER;
            CurrentNode->active = 1;
            CurrentNode->backgroud_color = "\033[42m";
            break;
        case ZOMBIE:
            GenerateNodePosition(NodeArray, CurrentNode, MaxSize);
            CurrentNode->letter = ZOMBIE_LETTER;
            CurrentNode->active = 1;
            CurrentNode->backgroud_color = "\033[41m";
            CurrentNode->points = -20.0;
            break;
        case SUPPLY:
            GenerateNodePosition(NodeArray, CurrentNode, MaxSize);
            CurrentNode->letter = SUPPLY_LETTER;
            CurrentNode->active = 1;
            CurrentNode->backgroud_color = "\033[44m";
            CurrentNode->points = 20.0;
            break;
        case TRAP:
            GenerateNodePosition(NodeArray, CurrentNode, MaxSize);
            CurrentNode->letter = TRAP_LETTER;
            CurrentNode->active = 1;
            CurrentNode->backgroud_color = "\x1b[48;5;244m";
            CurrentNode->points = -20.0;
            break;
        case EXIT:
            CurrentNode->x = MaxSize - 1;
            CurrentNode->y = MaxSize - 1;
            CurrentNode->letter = 'X';
            CurrentNode->points = 30.0;
            CurrentNode->backgroud_color = "\033[47m";
            CurrentNode->active = 1;
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