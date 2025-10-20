#include "adjacency.h"
#include "list.h"


t_adjacency_list createAdjacencyList(int size) {

        t_adjacency_list adjList;
        adjList.size = size;
        adjList.array = (t_list *)malloc(size * sizeof(t_list));
        if (adjList.array == NULL) {
                printf("Error allocating memory for adjacency list\n");
                exit(1);
        }
        for (int i = 0; i < size; i++) {
                adjList.array[i].head = createEmptyList;
        }
        return adjList;

};

void displayAdjacencyList(t_adjacency_list * adj) {
        for (int i = 0; i < adj->size; i++) {
                printf("List for vertex %d: ",i);
                displayList(adj);
        }

}

t_adjacency_list readGraph(const char *filename) {
        FILE *file = fopen(filename, "rt"); // read-only, text
        int nbvert, start, end;
        float proba;
        //declare the variable for the adjacency list
        t_adjacency_list adjList;
        if (file == NULL)
        {
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
        }
        // first line contains number of vertices
        if (fscanf(file, "%d", &nbvert) != 1)
        {
        perror("Could not read number of vertices");
        exit(EXIT_FAILURE);
        }
        //Initialise an empty adjacency list using the number of vertices
        adjList = createAdjacencyList(nbvert);
        while (fscanf(file, "%d %d %f", &start, &end, &proba) == 3)
        {

        // we obtain, for each line of the file, the values
        // start, end and proba
        addCell(adjList.array[start].head, end, proba);
        
        //Add the edge that runs from 'start' to ‘end’ with the
        //probability 'proba' to the adjacency list
        }
        fclose(file);
        return adjList;
}
