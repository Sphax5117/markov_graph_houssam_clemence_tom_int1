#ifndef ADJACENCY_H
#define ADJACENCY_H
#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct s_adjacency_list {

        t_list * array;
        int size;

} t_adjacency_list;


t_adjacency_list * createAdjacencyList(int size);
t_adjacency_list readGraph(const char *filename);
void displayAdjacencyList(t_adjacency_list * adj);

#endif ADJACENCY_H
