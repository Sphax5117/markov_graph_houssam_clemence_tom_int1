#include "adjacency.h"


adjacency_list createAdjecencyList(int size) {

        adjacency_list adjList;
        adjList.size = size;


        adjList.array = (list *)malloc(size * sizeof(list));
        if (adjList.array == NULL) {
                printf("Error allocating memory for adjacency list\n");
                exit(1);

        }
        for (int i = 0; i < size; i++) {
                adjList.array[i].head = NULL;
        }
        return adjList;

};

void displayAdjacencyList(adjacency_list * adj) {
        for (int i = 0; i < adj->size; i++) {

                printf("List for vertex %d: ",i, displayList(list));
        }

}
