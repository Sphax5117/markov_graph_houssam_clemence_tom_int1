//
// Created by cleme on 07/11/2025.
//
//en gros tarjan graphe il regroupe les sommets connectés entre eux en classes et se regroupement s'appelle une partition
#include "tarjan.h"
t_tarjan_vertex * tarjanArr(t_adjacency_list * graph){//creation of an array
    int n = graph->size;
    t_tarjan_vertex * vertices = (t_tarjan_vertex*)malloc((n+1)*sizeof(t_tarjan_vertex));
    //on alloue meoire pour n+1 car sommet de 1 a n
    if (vertices==NULL){
        perror("error");
        exit(EXIT_FAILURE);
    }
    for (int i=1;i<=n;i++){
        vertices[i].id  = i;
        vertices[i].number = -1;
        vertices[i].accessnb = -1;
        vertices[i].boolind = 0;//stack
    }
    return vertices;
}
