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

    result->rows = n;
    result->cols = n;

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

void copyMatrix(t_matrix dest, t_matrix src) {
    //on verifie la taille de la matrice source et la matrice de destination
    if (dest.rows != src.rows || dest.cols != src.cols) {
        fprintf(stderr, "Error: the matices aren't of the same size to be copied.\n");
        return;
    }

    // ici on cosidure que la pour realiser les copies des valeurs de la matrice on prend la taille des lignes
    int n = src.rows;


    for (int i = 0; i < n; i++) {       // ca parcourt les lignes
        for (int j = 0; j < n; j++) {   // et les colonnes
            // L'opération de copie elle-même
            dest.data[i][j] = src.data[i][j];
        }
    }
}