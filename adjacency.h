#ifndef ADJACENCY_H
#define ADJACENCY_H

#include <stdio.h>
#include <stdlib.h>


typedef struct {

        list * array;
        int size;

} adjacency_list;


adjacency_list * createAdjacencyList(int size);

void displayAdjacencyList(adjacency_list * adj);

#endif ADJACENCY_H
