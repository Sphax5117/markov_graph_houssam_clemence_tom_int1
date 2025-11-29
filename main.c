#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * @brief Helper function to set file paths based on the operating system.
 */
void setup_filepaths(char *f1, char *f2, char *bonus, char *project) {
    #ifdef _WIN32
        snprintf(f1, 256, "data\\exemple_valid_step3.txt");
        snprintf(f2, 256, "data\\test_bench\\exemple_valid_step3.txt");
        snprintf(bonus, 256, "data\\test_bench\\graph_bonus.txt");
        snprintf(project, 256, "data\\math_project.txt");
    #else
        snprintf(f1, 256, "data/exemple2.txt");
        snprintf(f2, 256, "data/exemple2.txt");
        snprintf(bonus, 256, "data/test_bench/graph_bonus.txt");
        snprintf(project, 256, "data/math_project.txt");
    #endif
}

/**
 * @brief Main entry point of the program.
 */
int main() {
    // 1. Setup Configuration
    char filename[256], filename2[256], bonus[256], project[256];
    setup_filepaths(filename, filename2, bonus, project);

    // ============================================================
    // PART 1: Graph Loading and Markov Property Check
    // ============================================================
    printf("\nThe first file to be loaded is : %s\n\n", filename);
    printf("PART 1 - BEGINNING OF THE TESTS\n\n");

    t_adjacency_list *adj = readGraph(filename);
    displayAdjacencyList(adj);

    if (isMarkovGraph(adj)) {
        printf("\nThe graph is a Markov Graph\n\n");
    } else {
        printf("\nThe graph is not a Markov Graph\n");
    }

    mermaidGenerator(adj);
    printf("-------------------------------\n");

    // ============================================================
    // PART 2: Tarjan's Algorithm and Components
    // ============================================================
    printf("PART 2 - BEGINNING OF THE TESTS\n");

    t_partition *partition = tarjan(adj);
    displayTarjan(partition);

    // Map vertices to their Tarjan components
    int *vertex_to_class = malloc((adj->size + 1) * sizeof(int));
    if (vertex_to_class == NULL) {
        perror("malloc vertex_to_class");
        exit(EXIT_FAILURE);
    }
    createvertextoclass(partition, vertex_to_class, adj->size);

    // Analyze links between components and generate Hasse diagram
    t_link_array links;
    Linkslist(partition, adj, vertex_to_class, &links);
    graphCharacteristics(partition, &links);
    mermaidHasse(partition, &links);

    free(vertex_to_class);
    free(links.links);
    printf("-------------------------------\n");

    // ============================================================
    // PART 3: Matrix Operations and Stationary Distribution
    // ============================================================
    printf("PART 3 - BEGINNING OF THE TESTS\n\n");
    printf("\nThe second file to be loaded is : %s\n\n", filename2);

    t_adjacency_list *adj2 = readGraph(filename2);
    t_matrix *m1 = createMatrixFromAdjacency(adj2);

    printf("\nMatrix M:\n\n");
    displayMatrix(m1);

    // --- Matrix Powers (M^3 and M^7) ---
    t_matrix *current_matrix = m1;
    for (int i = 1; i < 7; i++) {
        t_matrix *next_matrix = multiplyMatrices(current_matrix, m1);
        current_matrix = next_matrix; // Note: Intermediate matrices should ideally be freed here
        
        if (i + 1 == 3) {
            printf("\nMatrix M^3:\n\n");
            displayMatrix(current_matrix);
        }
        if (i + 1 == 7) {
            printf("\nMatrix M^7:\n\n");
            displayMatrix(current_matrix);
        }
    }

    // --- Convergence Check ---
    int n = 0;
    t_matrix *m2 = multiplyMatrices(m1, m1);
    t_matrix *curr2 = m2;
    float difference = matrixDifference(m2, m1); 
    
    while(difference >= 0.01) {
        t_matrix *next = multiplyMatrices(curr2, m1);
        difference = matrixDifference(next, curr2); 
        curr2 = next; // Note: Previous 'curr2' should ideally be freed here
        n++;
    }
    printf("\nThe matrix will be stationnary at n = %d\n\n", n);

    // --- Component Analysis (Submatrix) ---
    t_partition *tarjM = tarjanWithoutPrints(adj2);
    displayTarjan(tarjM);

    int compo_index = 0;
    t_matrix *subMat = subMatrix(m1, tarjM, compo_index);
    printf("Below, the matrix for component C%d\n\n", compo_index + 1);
    displayMatrix(subMat);

    // Prepare real IDs for final distribution display
    int sub_size = subMat->nbrows;
    int *real_ids = malloc(sub_size * sizeof(int));
    if (real_ids == NULL) {
        perror("malloc real_ids");
        exit(EXIT_FAILURE);
    }

    t_class current_class = tarjM->classes[compo_index];
    if (current_class.size != sub_size) {
        printf("WARNING: Class size (%d) != Matrix size (%d)\n", current_class.size, sub_size);
    }

    for (int k = 0; k < sub_size; k++) {
        real_ids[k] = current_class.vertices[k].id;
    }

    // --- Stationary Distribution for Component ---
    t_matrix *mDistrib = multiplyMatrices(subMat, subMat);
    t_matrix *curr = mDistrib;
    float diff = matrixDifference(mDistrib, subMat); 
    
    while(diff >= 0.01) {
        t_matrix *next = multiplyMatrices(curr, subMat);
        diff = matrixDifference(next, curr); 
        freeMatrix(curr);
        curr = next;
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
    printf("-------------------------------\n");

    // ============================================================
    // PART 3 (BONUS): Period Calculation
    // ============================================================
    printf("PART 3 (BONUS) - BEGINNING OF THE TESTS\n\n");

    t_adjacency_list *adjBonus = readGraph(bonus);
    t_partition *tarjBonus = tarjanWithoutPrints(adjBonus);
    
    int compo_index_bonus = 0;
    t_matrix *mat3 = createMatrixFromAdjacency(adjBonus);
    t_matrix *subMatBonus = subMatrix(mat3, tarjBonus, compo_index_bonus);
    
    int period = getPeriod(subMatBonus);
    printf("The period of the submatrix is %d\n", period);

    printf("-------------------------------\n");
    printf("Project part - BEGINNING OF THE TESTS\n\n");
    printf("\nThe second file to be loaded is : %s\n\n", project);
    t_adjacency_list *prjAdj = readGraph(project);
    t_matrix *prjM = createMatrixFromAdjacency(prjAdj);
    t_matrix * rowVector = createRowVector(prjAdj->size, 2); //we create the Π(0) vector, at state 2.
    printf("\nMatrix M:\n\n");
    displayMatrix(prjM);
    printf("\nRow vector Π(0):\n\n");
    displayRowVector(rowVector);

    // This part was produced by Gemini 3 pro
    FILE *fp = fopen("distribution.csv", "w");
    if (fp) {
        fprintf(fp, "n");
        for(int k=0; k < rowVector->nbcols; k++) fprintf(fp, ",State%d", k);
        fprintf(fp, "\n");

        fprintf(fp, "0");
        for(int k=0; k < rowVector->nbcols; k++) fprintf(fp, ",%f", rowVector->data[0][k]);
        fprintf(fp, "\n");
    }
    // End of part produced by Gemini 3 pro

    // Π(n+1)=Π(n)P
    // For n=1, Π(1)=Π(0)P.
    // For n=2, Π(2)=Π(0)P^2
    t_matrix *current_matrix_project = prjM;
    printf("\nRow vector Π(1)= Π(0)M:\n\n");

    // This part was produced by Gemini 3 pro
    t_matrix *pi_1 = multiplyMatricesIrregular(rowVector,prjM);
    displayRowVector(pi_1);

    if (fp) {
        fprintf(fp, "1");
        for(int k=0; k < pi_1->nbcols; k++) fprintf(fp, ",%f", pi_1->data[0][k]);
        fprintf(fp, "\n");
    }
    // End of part produced by Gemini 3 pro

    for (int i = 1; i < 50; i++) {
        t_matrix *next_matrix_project = multiplyMatrices(current_matrix_project, prjM); //the M^N matrix
        current_matrix_project = next_matrix_project; 

        // This part was produced by Gemini 3 pro
        t_matrix *pi_n = multiplyMatricesIrregular(rowVector, current_matrix_project);

        if (fp) {
            fprintf(fp, "%d", i + 1);
            for(int k=0; k < pi_n->nbcols; k++) fprintf(fp, ",%f", pi_n->data[0][k]);
            fprintf(fp, "\n");
        }
        // End of part produced by Gemini 3 pro
        
        if (i + 1 == 2) {
            printf("\nRow vector Π(2)= Π(0)M^2:\n\n");
            displayRowVector(multiplyMatricesIrregular(rowVector,current_matrix_project));
        }
        if (i + 1 == 10) {
            printf("\nRow vector Π(10)= Π(0)M^10:\n\n");
            displayRowVector(multiplyMatricesIrregular(rowVector,current_matrix_project));
        }
        if (i + 1 == 50) {
            printf("\nRow vector Π(50)= Π(0)M^50:\n\n");
            displayRowVector(multiplyMatricesIrregular(rowVector,current_matrix_project));
        }
    }
    if (fp) fclose(fp);
    printf("\nData exported to 'distribution.csv'\n");
    return 0;
}
