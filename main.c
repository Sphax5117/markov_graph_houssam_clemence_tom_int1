#include <stdio.h>
#include "main.h"

int main() {
    char filename[256];
    char filename2[256]; // for part 3
    #ifdef _WIN32
        snprintf(filename, sizeof(filename), "..\\data\\exemple_valid_step3.txt");
        snprintf(filename2, sizeof(filename), "..\\data\\test_bench\\exemple_valid_step3.txt");
    #else
        snprintf(filename, sizeof(filename), "data/exemple_valid_step3.txt");
        snprintf(filename2, sizeof(filename), "data/test_bench/exemple_valid_step3.txt");
    #endif
    t_adjacency_list * adj;
    printf("\nThe first file to be loaded is : %s\n\n", filename);
    printf("PART 1 - BEGINNING OF THE TESTS\n\n");
    adj = readGraph(filename);
    displayAdjacencyList(adj);
    if (isMarkovGraph(adj)) {
        printf("\nThe graph is a Markov Graph\n\n");
    } else {
        printf("\nThe graph is not a Markov Graph\n");
    }
    mermaidGenerator(adj);
    printf("-------------------------------\n");
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
    printf("-------------------------------\n");
    printf("PART 3 - BEGINNING OF THE TESTS\n\n");
    printf("\nThe second file to be loaded is : %s\n\n", filename2);
    t_adjacency_list * adj2;
    adj2 = readGraph(filename2);
    t_matrix * m1;
    m1 = createMatrixFromAdjacency(adj2);
    printf("\nMatrix M:\n\n");
    displayMatrix(m1);
    t_matrix *current_matrix = m1;
    for (int i = 1; i < 7; i++) {
        t_matrix *next_matrix = multiplyMatrices(current_matrix, m1);
        current_matrix = next_matrix;
        
        if (i + 1 == 3) {
            printf("\nMatrix M^3:\n\n");
            displayMatrix(current_matrix);
        }
        if (i + 1 == 7) {
            printf("\nMatrix M^7:\n\n");
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
    printf("\nThe matrix will be stationnary at n = %d\n\n", n);
    t_partition * tarjM;
    tarjM = tarjanWithoutPrints(adj2);
    displayTarjan(tarjM);
    int compo_index = 0;
    t_matrix * subMat;
    subMat = subMatrix(m1, tarjM, compo_index);
    printf("Below, the matrix for component C%d\n\n", compo_index + 1);
    displayMatrix(subMat);
    /// THE PART BELOW WAS DONE BY GEMINI 3 PRO IN ORDER TO HAVE THE CORRECT PARAMETERS IN displayFinalDistribution
    //
    //
    int sub_size = subMat->nbrows;
    int *real_ids = malloc(sub_size * sizeof(int));
    if (real_ids == NULL) {
        perror("malloc real_ids");
        exit(EXIT_FAILURE);
    }
    t_class current_class = tarjM->classes[compo_index];
    // Check if matrix size matches class size (Sanity Check)
    if (current_class.size != sub_size) {
        printf("WARNING: Class size (%d) != Matrix size (%d)\n", current_class.size, sub_size);
    }

    // ARRAY ITERATION (No Linked List)
    for (int k = 0; k < sub_size; k++) {
        // According to tarjan.h: vertices is an array of t_tarjan_vertex
        real_ids[k] = current_class.vertices[k].id;
    }
    //
    //
    /// THE PART ABOVE WAS DONE BY GEMINI 3 PRO IN ORDER TO HAVE THE CORRECT PARAMETERS IN displayFinalDistribution
    t_matrix * mDistrib = multiplyMatrices(subMat, subMat);
    t_matrix *curr = mDistrib;
    float diff = matrixDifference(mDistrib, subMat); 
    while(diff >= 0.01) {
        t_matrix *next= multiplyMatrices(curr, subMat);
        diff = matrixDifference(next, curr); 
        freeMatrix(curr);
        curr= next;
    }
    printf("Stationary Matrix for the classes (rounded) :\n\n");
    displayMatrix(curr);
    if (real_ids != NULL) {
        displayFinalDistribution(curr, real_ids, sub_size); 
        free(real_ids);
    } else {
        printf("Distribution for the classes (Index-based):\n");
        displayMatrix(curr);
    }

    return 0;
}
