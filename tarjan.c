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


//fonction tarjan(graphe G)
  // num := 0
   //P := pile vide
   //partition := ensemble vide


   // renvoyer partition
// fin de fonction
void tarjan(t_adjacency_list * graph) {
    int * num;
    num = 0;
    t_stack * stack = createStack();
    t_partition * partition = createPartition();
    t_tarjan_vertex * vertices = tarjanArr(graph);

    if(vertices==NULL){
        perror("error");
        exit(EXIT_FAILURE);
    }
    for (int i=1;i<=graph->size;i++){
            vertices[i].id  = i;    
            if (vertices[i].number == -1) {
                parcours(&vertices[i], stack, partition, graph, num);
            }
    }
    return partition;
}

void parcours(t_tarjan_vertex * v, t_stack * stack, t_partition * partition, t_adjacency_list * graph, int * num) {
    v->number = num;
    v->accessnb = num;
    num++;
    pushStack(v->number, stack);
    v->boolind =1;
    for ()  //chaque w successeur de v 

    // check in adjacency list the successors of the id of v
    // go for each one of them 
    {
        if (w->number == NULL) {
            parcours(w);
            v->accessnb = minimum(v->accessnb, w.accessnb);
        } else {
            v->accessnb = minimum(v->accessnb, w.number);
        }
    }
    if (v->accessnb == v->number) {
        t_class C = createEmptyClass()
        while (w != v) {//weird 
            w = pop(stacks);
            w.boolind = 0;
            addToClass(w);
        }
        addToPartition(partition, C)


    //pour chaque sommet v de G
    // si v.num n est pas défini
    //parcours(v)
   }
