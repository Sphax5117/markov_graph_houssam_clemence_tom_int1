//
// Created by cleme on 07/11/2025.
//
//en gros tarjan graphe il regroupe les sommets connectés entre eux en classes et se regroupement s'appelle une partition
#include "tarjan.h"
t_tarjan_vertex * tarjanArr(t_adjacency_list * graph){//creation of an array
    int n = graph->size;
    t_tarjan_vertex * vertices = (t_tarjan_vertex*)malloc((n+1)*sizeof(t_tarjan_vertex)); //array of vertices
    //on alloue meoire pour n+1 car sommet de 1 a n
    if (vertices==NULL){
        perror("error");
        exit(EXIT_FAILURE); //to be changed, not clean
    }
    for (int i=0;i<=n;i++){
        vertices[i].id  = i+1; //to have node 1 at position 0 and so on.
        vertices[i].number = -1;
        vertices[i].accessnb = -1;
        vertices[i].boolind = 0;//stack
    }
    return vertices;
}


void displayTarjan(t_tarjan_vertex * vertices, int size) {
    if (vertices == NULL) {
        perror("error");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        printf("ID: %d, Number: %d, AccessNb: %d, BoolInd: %d\n", 
            vertices[i].id, vertices[i].number, vertices[i].accessnb, vertices[i].boolind);
    }
}

//fonction tarjan(graphe G)
  // num := 0
   //P := pile vide
   //partition := ensemble vide


   // renvoyer partition
// fin de fonction
void tarjan(t_adjacency_list * graph) {
    int num_value = 0;
    int * num = &num_value;
    t_stack * stack;
    stack = createStack(graph->size);
    t_partition * partition;
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
    return;
}

void parcours(t_tarjan_vertex * v, t_stack * stack, t_partition * partition, t_adjacency_list * graph, int *p_num) {
    v->number = *p_num;
    v->accessnb = *p_num;
    (*p_num)++;
    pushStack(v->number, stack);
    v->boolind =1;
    t_cell * current = graph->array[v->id].head;
    while (current != NULL) {
        printf("Vertex %d -> %d\n", v->id, current->destination);
        current = current->next;
    }
    return;
    // }
    // for ()  //chaque w successeur de v 

    // // id -> number of vertex in the adjency list.
    // // check in adjacency list the successors of the id of v
    // // go for each one of them 
    // {
    //     if (w->number == NULL) {
    //         parcours(w);
    //         v->accessnb = minimum(v->accessnb, w.accessnb);
    //     } else {
    //         v->accessnb = minimum(v->accessnb, w.number);
    //     }
    // }
    // if (v->accessnb == v->number) {
    //     t_class C = createEmptyClass()
    //     while (w != v) {//weird 
    //         w = pop(stacks);
    //         w.boolind = 0;
    //         addToClass(w);
    //     }
    //     addToPartition(partition, C)


    // //pour chaque sommet v de G
    // // si v.num n est pas défini
    // //parcours(v)
   }