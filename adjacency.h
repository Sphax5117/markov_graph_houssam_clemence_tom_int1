#ifndef ADJACENCY_H
#define ADJACENCY_H

#include <stdio.h>
#include <stdlib.h>


typedef struct s_adjacency_list {

        list * array;
        int size;

} t_adjacency_list;


t_adjacency_list * createAdjacencyList(int size);
t_adjacency_list readGraph(const char *filename);
void displayAdjacencyList(adjacency_list * adj);

#endif ADJACENCY_H
