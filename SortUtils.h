#ifndef SORTUTILS_H
#define SORTUTILS_H

    #include "NodeUtils.h"
    
    int Partition(Node * NodeArray[], unsigned int InitialIndex, unsigned int FinalIndex);
    void QuickSort(Node * NodeArray[], unsigned int InitialIndex, unsigned int FinalIndex);
#endif