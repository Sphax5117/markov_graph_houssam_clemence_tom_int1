//
// Created by Houss on 20/11/2025.
//
#include <stdio.h>
#include "matrix.h"

t_matrix* createEmptyMatrix(int n) {
    /**
     * @brief Creates an empty matrix of size n*n, filled with 0. 
     * This matrix uses double pointers 
    *
    * @param n int : The size of the matrix
    * @return t_matrix The matrix of size n*n
    */
    t_matrix* result = (t_matrix*)malloc(sizeof(t_matrix));
    if (result == NULL) {
        perror("Allocation error for matrix structure");
        exit(EXIT_FAILURE);
    }

    

    result->nbrows = n;
    result->nbcols = n;

    //we allocate memory for each data space 
    result->data = (float**)malloc(n * sizeof(float*));
    if (result->data == NULL) {
        perror("Allocation error for the rows");
        free(result); 
        exit(EXIT_FAILURE);
    }

    // We allocate the data that we add and set it to 0
    for (int i = 0; i < n; i++) {
        result->data[i] = (float*)calloc(n, sizeof(float)); //calloc initialize with 0 so perfect
        if (result->data[i] == NULL) {
            perror("Allocation error for the data");
            for (int k = 0; k < i; k++) {
                free(result->data[k]);
            }
            free(result->data);
            free(result);
            exit(EXIT_FAILURE); //we free to avoid memory leaks
        }
    }
    return result;
}

void copyMatrix(t_matrix * dest, t_matrix * src) {
   /**
     * @brief This function copies the content of the source matrix to the destination matrix
    *
    * @param src * t_matrix : the source matrix
    * @param dest * t_matrix : the destination matrix
    * @return void 
    */

    //We check that both matrices are the same size
    if (dest->nbrows != src->nbrows || dest->nbcols != src->nbcols) {
        fprintf(stderr, "Error: the matices aren't of the same size to be copied.\n");
        return;
    }

   
    int n = src->nbrows;


    for (int i = 0; i < n; i++) {      
        for (int j = 0; j < n; j++) {  
            dest->data[i][j] = src->data[i][j];
        }
    }
}



t_matrix * createMatrixFromAdjacency(t_adjacency_list * adj) {
    /**
     * @brief This function creates, based on an adjacency list, the associated matrix.
    *
    * @param adj * t_adjacency_list: the adjacency list to extract the matrix from
    * @return t_matrix : the matrix that was created 
    */
    t_matrix * matrix;
    matrix = createEmptyMatrix(adj->size);
    for (int i = 0; i < adj->size; i++) {
        const t_cell *curr = adj->array[i].head;
            while (curr) {
                int j = curr->destination -1; //-1 bcs our nodes start at 1
                //as we only need to fill nodes connected to the 1st, the 2nd, etc...
                // we use only the destinations as indexes (at first, i was going for a double for loop, but Gemini 3 Pro advised me to do that which is way smart and efficient)
            if (j >= 0 && j < matrix->nbcols) { //we check that we don't fill non-existent spots in the matrix
                matrix->data[i][j] = curr->probability;
            }
            curr = curr->next;
        }
    }
    return matrix;
}
t_matrix *multiplyMatrices(t_matrix * M, t_matrix * N) {
    /**
     * @brief This function multiplies to matrix (matrix multiplation from Linear Algebra), and return the result
    * @param M * t_matrix : the first matrix to be multiplied
    * @param N * t_matrix : the second matrix to be multiplied
    * @return N t_matrix : the result of the multiplication of the two matrixs 
    */
    if (M->nbcols != N->nbrows) {
        fprintf(stderr, "Erreur: Les matrices ne sont pas compatibles pour la multiplication.\n");
        exit(EXIT_FAILURE);
    }

    int n = M->nbrows; 
    t_matrix * R = createEmptyMatrix(n); 
    for (int i = 0; i < n; i++) {
        
        for (int j = 0; j < n; j++) {
                        // Use double for higher precision during accumulation 
            double sum = 0.0; 
            for (int k = 0; k < n; k++) {
                sum += (double)M->data[i][k] * (double)N->data[k][j];
            }
            // Cast back to float for storage
            R->data[i][j] = (float)sum;
        }
    
        }
        return R;
    }


float matrixDifference(t_matrix * matrixA, t_matrix * matrixB) {
    /**
     * @brief This function calculate the difference between two matrices, using the formula : Sum(i)Sum(j)(|A_ij - B_ij|)
    * @param M * t_matrix : the first matrix to be multiplied
    * @param N * t_matrix : the second matrix to be multiplied
    * @return N t_matrix : the result of the multiplication of the two matrixs 
    */
    float result = 0.0;
    int n = matrixA->nbcols;
    if (n != matrixA->nbrows || n != matrixB->nbcols || n != matrixB->nbrows) {
        fprintf(stderr, "Error ( matrixDifference() ): Matrices aren't the same size\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result += fabs(matrixA->data[i][j] - matrixB->data[i][j]); //fabs is used to have absolute value of floats
        }
    }
    return result;
}

/**
 * @brief Displays the matrix to the standard output.
 *
 * @param m A pointer to the matrix to display.
 */
void displayMatrix(t_matrix * m){
    int n = m->nbrows;
    if (n != m->nbcols) {
        fprintf(stderr, "Error ( displayMatrix() ): Matrices aren't the same size\n");
        exit(EXIT_FAILURE);
    } 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("| %6.2f ", m->data[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
    return;
}

t_matrix * subMatrix(t_matrix * matrix, t_partition * part, int compo_index) {
    /**
     * @brief Extracts a submatrix corresponding to a specific
    component of a graph partition.
    *
    * @param matrix The original adjacency matrix of the graph.
    * @param part The partition of the graph into strongly
    connected components.
    * @param compo_index The index of the component to extract.
    * @return t_matrix The submatrix corresponding to the
    specified component.
    */
   t_matrix * m;
   int n = part->classes[compo_index].size;
   m = createEmptyMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int global_row = part->classes[compo_index].vertices[i].id - 1; //as our nodes start at 1, we need to remove 1 to have the "real index"
            int global_col = part->classes[compo_index].vertices[j].id - 1;

            m->data[i][j] = matrix->data[global_row][global_col];
        }
    }
    return m;
}
// the function below was done by Gemini Pro 3 in order to display the final distribution in a clean manner
/**
 * @brief Displays the final stationary distribution of the Markov chain.
 *
 * @param converged The converged matrix representing the stationary distribution.
 * @param real_ids An array of real vertex IDs corresponding to the matrix indices.
 * @param size The size of the matrix/distribution.
 */
void displayFinalDistribution(t_matrix *converged, int *real_ids, int size) {
    if (converged == NULL || real_ids == NULL) return;

    printf("\n\n--- Stationary Distribution (Limit) ---\n\n");
    printf("| State | Probability |\n");
    printf("|-------|-------------|\n");

    // We only need to read the first row (row 0) because at stationarity, 
    // all rows in the matrix are identical.
    for (int j = 0; j < size; j++) {
        double prob = converged->data[0][j];
        int node_id = real_ids[j];
        
        // Display formatted: ID | Percentage
        printf("|   %2d  |   %5.2f%%    |\n", node_id, prob * 100);
    }
    printf("---------------------------------------\n");
}

/**
 * @brief Frees the memory allocated for a matrix.
 *
 * @param m A pointer to the matrix to free.
 */
void freeMatrix(t_matrix * m) {
    int n = m->nbcols;
    if (n != m->nbcols) {
        fprintf(stderr, "Error ( displayMatrix() ): Matrices aren't the same size\n");
        exit(EXIT_FAILURE);
    } 
    for (int i = 0; i < n; i++) {
           free(m->data[i]);
            m->data[i] = NULL;
        }
    free(m->data);
    m->data = NULL;
    free(m);
    m = NULL;
}