//
// Created by Houss on 20/11/2025.
//

#ifndef INC_2526_TI301_PJT_MATRIX_H
#define INC_2526_TI301_PJT_MATRIX_H
#include <stdlib.h>
#include <math.h>
#include "adjacency.h"
#include "tarjan.h"

typedef struct {
    int nbrows;
    int nbcols;
    float** data;
} t_matrix;

t_matrix * createEmptyMatrix(int n);
void copyMatrix(t_matrix * destination, t_matrix * source);
float matrixDifference(t_matrix * matrixA, t_matrix * matrixB);
t_matrix * createMatrixFromAdjacency(t_adjacency_list * adj);
t_matrix *multiplyMatrices(t_matrix * M, t_matrix * N);
void displayMatrix(t_matrix * m);
t_matrix * subMatrix(t_matrix * matrix, t_partition * part, int compo_index);

#endif //INC_2526_TI301_PJT_MATRIX_H