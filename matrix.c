//
// Created by Houss on 20/11/2025.
//
#include <stdio.h>
#include "matrix.h"

t_matrix* createEmptyMatrix(int n) {
    t_matrix* result = (t_matrix*)malloc(sizeof(t_matrix));
    if (result == NULL) {
        perror("Allocation error for matrix structure");
        exit(EXIT_FAILURE);
    }

    //Tom (20/11) : j'ai transformé la fonction pour return des pointers

    result->nbrows = n;
    result->nbcols = n;

    // la on fait une allocation des pointeurs des lignes n
    result->data = (float**)malloc(n * sizeof(float*));
    if (result->data == NULL) {
        perror("Allocation error for the rows");
        free(result); // Don't forget to free the struct
        exit(EXIT_FAILURE);
    }

    // ici on fait une allocation des données qu'on avait et ensuite une initialisation à 0 comme demandé
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
    //on verifie la taille de la matrice source et la matrice de destination
    if (dest->nbrows != src->nbrows || dest->nbcols != src->nbcols) {
        fprintf(stderr, "Error: the matices aren't of the same size to be copied.\n");
        return;
    }

    // ici on cosidure que la pour realiser les copies des valeurs de la matrice on prend la taille des lignes
    int n = src->nbrows;


    for (int i = 0; i < n; i++) {       // ca parcourt les lignes
        for (int j = 0; j < n; j++) {   // et les colonnes
            // L'opération de copie elle-même
            dest->data[i][j] = src->data[i][j];
        }
    }
}



t_matrix * createMatrixFromAdjacency(t_adjacency_list * adj) {
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
    // Dans ce contexte, on suppose n x n. On vérifie juste les dimensions.
    if (M->nbcols != N->nbrows) {
        fprintf(stderr, "Erreur: Les matrices ne sont pas compatibles pour la multiplication.\n");
        exit(EXIT_FAILURE);
    }

    int n = M->nbrows; 
    t_matrix * R = createEmptyMatrix(n); 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float sum = 0.0f;
            for (int k = 0; k < n; k++) {
                sum += M->data[i][k] * N->data[k][j];
            }
            R->data[i][j] = sum;
        }
    }
    return R;
}

float matrixDifference(t_matrix * matrixA, t_matrix * matrixB) {
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
    return;
}
