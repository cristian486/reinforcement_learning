#ifndef NODEUTILS_H
#define NODEUTILS_H
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    
    #define MAX_SIZE       8
    #define PLAYER_LETTER 'P'
    #define ZOMBIE_LETTER 'Z'
    #define SUPPLY_LETTER 'S'
    #define EXIT_LETTER   'X'
    #define TRAP_LETTER   'T'
    #define MAX_NODE_ARRAY_SIZE 8

    typedef struct {
        double points;
        unsigned int x;
        unsigned int y;
        unsigned int active;
        unsigned char letter;
        unsigned char * backgroud_color;
    } Node;

    typedef enum {
            PLAYER = 0,
            ZOMBIE = 1,
            SUPPLY = 2,
            TRAP = 3,
            EXIT = 4
    } NodeType;

    #include "SortUtils.h"

    void FreeNodeArray(Node * NodeArray[]);
    void ResetNodeArray(Node * NodeArray[]);
    void ReInitializeNodeArray(Node * NodeArray[], unsigned int MaxSize);
    void GenerateNodePosition(Node * NodeArray[], Node * Node, unsigned int MaxSize);
    void VerifyIfIsOverlapping(Node * NodeArray[], unsigned int CoordinateX, unsigned int CoordinateY);
    Node * IsPositionOccupiedByNode(Node * NodeArray[], unsigned int CoordinateX, unsigned int CoordinateY);
    void InitializeNode(Node * NodeArray[], NodeType Type, unsigned int IndexOfNodeToInitialize, unsigned int MaxSize);
    void InitializeNodeArray(Node * NodeArray[], unsigned int * MemoryReservationError, unsigned int MaxSize);
#endif