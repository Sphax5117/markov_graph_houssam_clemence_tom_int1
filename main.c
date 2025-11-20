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

    int *vertex_to_class = malloc((adj->size + 1) * sizeof(int));
    if (vertex_to_class == NULL) {
        perror("malloc vertex_to_class");
        exit(EXIT_FAILURE);
    }
    createvertextoclass(partition, vertex_to_class, adj->size);
    t_link_array links;
    Linkslist(partition, adj, vertex_to_class, &links);
    graphCharacteristics(partition, &links);

    free(vertex_to_class);
    free(links.links);
    
    return 0;
}
//