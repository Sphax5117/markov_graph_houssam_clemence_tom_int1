//
// Created by cleme on 07/11/2025.
//
//en gros tarjan graphe il regroupe les sommets connectés entre eux en classes et se regroupement s'appelle une partition
#include "tarjan.h"
t_tarjan_vertex * tarjanArr(t_adjacency_list * graph){
    int n = graph->size;
    t_tarjan_vertex * vertices = (t_tarjan_vertex*)malloc((n+1)*sizeof(t_tarjan_vertex));
    if (vertices==NULL){
        perror("error");
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<=n; i++){
        vertices[i].id = i; 
        vertices[i].number = -1;
        vertices[i].accessnb = -1;
        vertices[i].boolind = 0;
    }
    return vertices;
}


void displayTarjan(t_partition * partition) {
    if (partition == NULL) {
        perror("error");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < partition->size; i++) {
        printf("Component C%d: {", i + 1);
        for (int j = 0; j < partition->classes[i].size; j++) {
            printf("%d", partition->classes[i].vertices[j].id);
            if (j < partition->classes[i].size - 1) {
                printf(",");
            }
        }
        printf("}\n");
    }
}

//fonction tarjan(graphe G)
  // num := 0
   //P := pile vide
   //partition := ensemble vide


   // renvoyer partition
// fin de fonction
t_partition * tarjan(t_adjacency_list * graph) {
    int num_value = 0;
    int * num = &num_value;
    t_stack * stack;
    stack = createStack(graph->size);
    t_partition * partition = (t_partition *)malloc(sizeof(t_partition));
    partition->classes = (t_class *)malloc(graph->size * sizeof(t_class));
    partition->size = 0;
    partition->capacity = graph->size;
    t_tarjan_vertex * vertices = tarjanArr(graph);

    if(vertices==NULL){
        perror("error");
        exit(EXIT_FAILURE);
    }
    for (int i=1;i<=graph->size;i++){
        if (vertices[i].number == -1) {
            parcours(&vertices[i], vertices, stack, partition, graph, num);
        }
    }
    return partition;
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

void parcours(t_tarjan_vertex * v, t_tarjan_vertex * vertices, t_stack * stack, t_partition * partition, t_adjacency_list * graph, int *p_num) {
    printf("iteration aaa\n");
    v->number = *p_num;
    v->accessnb = *p_num;
    (*p_num)++;
    pushStack(v->id, stack);
    v->boolind =1;
    t_cell * current = graph->array[v->id -1].head;
    t_tarjan_vertex * w;
    while (current != NULL) {
        printf("Vertex %d -> %d\n", v->id, current->destination);
        w = &vertices[current->destination]; //current destination -> successor of v.
        if (w->number == -1) {
            parcours(w, vertices, stack, partition, graph, p_num);
            if (w->accessnb < v->accessnb) {
                v->accessnb = w->accessnb;
            }
        } else if (w->boolind == 1) {
            if (w->number < v->accessnb) {
                v->accessnb = w->number;
            }
        }
        current = current->next;
    }
    if (v->accessnb == v->number) {
    printf("Found SCC root: vertex %d\n", v->id);
    t_class * C = createClass(graph);
    t_tarjan_vertex * w = NULL;
    int popped_id;
    do {
        popped_id = pop(stack);
        printf("Popping vertex with id %d from stack\n", popped_id);
        
        // Check if popped_id is valid (between 1 and graph->size)
        if (popped_id < 1 || popped_id > graph->size) {
            printf("Error: Invalid vertex ID popped: %d\n", popped_id);
            break;
        }
        
        w = &vertices[popped_id];
        w->boolind = 0;
        printf("Adding vertex %d to class\n", w->id);
        addToClass(C, w);
    } while(w->id != v->id);
    printf("Class size: %d\n", C->size);
    partition->classes[partition->size] = *C;
    partition->size += 1;
}
    return;
}