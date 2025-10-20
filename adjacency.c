#include "adjacency.h"
#include "list.h"

t_adjacency_list *createAdjacencyList(int size) {
    t_adjacency_list *adjList = malloc(sizeof *adjList);
    if (!adjList) { perror("malloc adjList"); exit(1); }

    adjList->size = size;
    adjList->array = malloc(sizeof *adjList->array * size);
    if (!adjList->array) { perror("malloc array"); exit(1); }

    for (int i = 0; i < size; i++)
        adjList->array[i] = *createEmptyList();

    return adjList;
}

void displayAdjacencyList(const t_adjacency_list *adj) {
    for (int i = 0; i < adj->size; i++) {
        printf("List for vertex %d:", i + 1);
        displayList(&adj->array[i]);
    }
}

t_adjacency_list *readGraph(const char *filename) {
    FILE *file = fopen(filename, "r");
    int nbvert, start, end;
    float proba;
    
    if (file == NULL) {
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }
    
    if (fscanf(file, "%d", &nbvert) != 1) {
        perror("Could not read number of vertices");
        exit(EXIT_FAILURE);
    }
    
    t_adjacency_list *adjList = createAdjacencyList(nbvert);
    
    while (fscanf(file, "%d %d %f", &start, &end, &proba) == 3) {
        addCell(&adjList->array[start-1], end, proba);
    }
    
    fclose(file);
    return adjList;
}