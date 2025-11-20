#include <stdio.h>
#include "main.h"

int main() {
    char filename[256];
    char filename2[256]; // for part 3
    #ifdef _WIN32
        snprintf(filename, sizeof(filename), "..\\data\\exemple_valid_step3.txt");
        snprintf(filename2, sizeof(filename), "..\\data\\test_bench\\exemple_meteo.txt");
    #else
        snprintf(filename, sizeof(filename), "data/exemple_valid_step3.txt");
        snprintf(filename2, sizeof(filename), "data/test_bench/exemple_meteo.txt");
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
    printf("PART 3 - BEGINNING OF THE TESTS\n");
    t_adjacency_list * adj2;
    adj2 = readGraph(filename2);
    t_matrix * m1;
    m1 = createMatrixFromAdjacency(adj2);
    displayMatrix(m1);
    t_matrix *current_matrix = m1;
    for (int i = 1; i < 7; i++) {
        t_matrix *next_matrix = multiplyMatrices(current_matrix, m1);
        current_matrix = next_matrix;
        
        if (i + 1 == 3) {
            printf("\nMatrix M^3:\n");
            displayMatrix(current_matrix);
        }
        if (i + 1 == 7) {
            printf("\nMatrix M^7:\n");
            displayMatrix(current_matrix);
        }
    }
    int n = 0;
    t_matrix * m2 = multiplyMatrices(m1,m1);
    t_matrix *curr2 = m2;
    float difference = matrixDifference(m2, m1); 
    while(difference >= 0.01) {
        t_matrix *next= multiplyMatrices(curr2, m1);
        difference = matrixDifference(next, curr2); 
        curr2 = next;
        n += 1;
    }
    printf("\nThe matrix will be stationnary at n = %d\n", n);

    return 0;
}
