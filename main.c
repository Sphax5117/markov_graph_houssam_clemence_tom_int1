#include <stdio.h>
#include "main.h"

int main() {
    char filename[256];
    #ifdef _WIN32
        snprintf(filename, sizeof(filename), "..\\data\\exemple_valid_step3.txt");
    #else
        snprintf(filename, sizeof(filename), "data/exemple_valid_step3.txt");
    #endif
    t_adjacency_list * adj;
    printf("PART 1 - BEGINNING OF THE TESTS\n");
    adj = readGraph(filename);
    displayAdjacencyList(adj);
    if (isMarkovGraph(adj)) {
        printf("The graph is a Markov Graph\n");
    } else {
        printf("The graph is not a Markov Graph\n");
    }
    mermaidGenerator(adj);
    printf("PART 2 - BEGINNING OF THE TESTS\n");
    t_partition * partition = tarjan(adj);
    displayTarjan(partition);
    
    return 0;
}
