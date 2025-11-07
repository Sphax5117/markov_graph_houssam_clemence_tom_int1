#include <stdio.h>
#include "main.h"

int main() {
    char filename[256];
    #ifdef _WIN32
        snprintf(filename, sizeof(filename), "..\\data\\exemple3.txt");
    #else
        snprintf(filename, sizeof(filename), "data/exemple3.txt");
    #endif
    t_adjacency_list * adj;
    adj = readGraph(filename);
    displayAdjacencyList(adj);
    if (isMarkovGraph(adj)) {
        printf("The graph is a Markov Graph\n");
    } else {
        printf("The graph is not a Markov Graph\n");
    }
    mermaidGenerator(adj);
    return 0;
}
