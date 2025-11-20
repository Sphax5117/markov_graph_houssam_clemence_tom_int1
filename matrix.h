//
// Created by Houss on 20/11/2025.
//

#ifndef INC_2526_TI301_PJT_MATRIX_H
#define INC_2526_TI301_PJT_MATRIX_H
#include <stdlib.h>
#include <math.h>

typedef struct {
    int rows;
    int cols;
    float** data;
} t_matrix;

t_matrix createEmptyMatrix(int n);

#endif //INC_2526_TI301_PJT_MATRIX_H