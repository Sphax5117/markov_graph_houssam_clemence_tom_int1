//
// Created by Houss on 20/11/2025.
//

#include "matrix.h"

t_matrix createEmptyMatrix(int n) {
    t_matrix result;
    result.rows = n;
    result.cols = n;

    // la on fait une allocation des pointeurs des lignes n
    result.data = (float**)malloc(n * sizeof(float*));
    if (result.data == NULL) {
        perror("Allocation error for the rows");
        exit(EXIT_FAILURE);
    }

    // ici on fait une allocation des données qu'on avait et ensuite une initialisation à 0 comme demandé
    for (int i = 0; i < n; i++) {
        result.data[i] = (float*)calloc(n, sizeof(float));
        if (result.data[i] == NULL) {
            perror("Allocation error for the data");
            for (int k = 0; k < i; k++) {
                free(result.data[k]);
            }
            free(result.data);
            exit(EXIT_FAILURE);
        }
    }
    return result;
}