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

t_class * createClass(t_adjacency_list * graph) {
        t_class *C = (t_class *)malloc(sizeof(t_class));
        if (C == NULL) {
            perror("error");
            exit(EXIT_FAILURE);
        }
        C->vertices = (t_tarjan_vertex *)malloc(graph->size * sizeof(t_tarjan_vertex));
        if (C->vertices == NULL) {
            perror("error");
            exit(EXIT_FAILURE);
        }
        C->size = 0;
        C->capacity = graph->size;
        return C;
}

void addToClass(t_class *C, t_tarjan_vertex *v) {
                if (C == NULL || v == NULL) {
                    perror("error");
                    exit(EXIT_FAILURE);
                }
                if (C->size >= C->capacity) {
                    printf("%d", C->size);
                    perror("error: class is full");
                    exit(EXIT_FAILURE);
                }
                C->vertices[C->size] = *v;
                C->size++;
}

void parcours(t_tarjan_vertex * v, t_stack * stack, t_partition * partition, t_adjacency_list * graph, int *p_num) {
    printf("iteration aaa\n");
    v->number = *p_num;
    v->accessnb = *p_num;
    (*p_num)++;
    pushStack(v->number, stack);
    v->boolind =1;
    t_cell * current = graph->array[v->id].head;
    t_tarjan_vertex * w;
    while (current != NULL) {
        printf("Vertex %d -> %d\n", v->id, current->destination);
        w = &v[current->destination]; //current destination -> successor of v.
            if (w->number == -1) { //if w number is null(initalize to -1)
                parcours(w, stack, partition, graph, p_num);
                if (v->accessnb < w->accessnb) {
                    v->accessnb = v->accessnb;
                } else {
                    v->accessnb = w->number;
                }
            }
        current = current->next;
    }
    if (v->accessnb == v->number) {
        t_class * C = createClass(graph);
        while(w->id != v->id) {
            w->number = pop(stack);
            w->boolind = 1;
            addToClass(C, w);
        }
        partition->classes = C;
        partition->size +=1;
    }
    return;
}