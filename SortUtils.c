#include "SortUtils.h"

int Partition(Node * NodeArray[], unsigned int InitialIndex, unsigned int FinalIndex) {
    unsigned int Pivot = NodeArray[FinalIndex]->x + NodeArray[FinalIndex]->y;
    unsigned int i = (InitialIndex - 1);

    for (int j = InitialIndex; j <= FinalIndex - 1; j++) {
        if ((NodeArray[j]->x +  NodeArray[j]->y) < Pivot) {
            i++;
            Node * Temp = NodeArray[i];
            NodeArray[i] = NodeArray[j];
            NodeArray[j] = Temp;
        }
    }
    
    Node * Temp = NodeArray[i + 1];
    NodeArray[i + 1] = NodeArray[FinalIndex];
    NodeArray[FinalIndex] = Temp;

    return (i + 1);
}

void QuickSort(Node * NodeArray[], unsigned int InitialIndex, unsigned int FinalIndex) {
    if (InitialIndex < FinalIndex) {
        unsigned int Part = Partition(NodeArray, InitialIndex, FinalIndex);
        QuickSort(NodeArray, InitialIndex, Part - 1);
        QuickSort(NodeArray, Part + 1, FinalIndex);
    }
}

