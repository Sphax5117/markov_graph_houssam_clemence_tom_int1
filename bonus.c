#include "bonus.h"

int gcd(int *vals, int nbvals) {
    //based on the name, we can assume that this function calculates the Greatest Common Divisor
    if (nbvals == 0) return 0; //if no values, the GCD is 0
    int result = vals[0]; //we init the result at the first value of the values list
    for (int i = 1; i < nbvals; i++) {
        int a = result;
        int b = vals[i];
        while (b != 0) {
            int temp = b; //Implementation of the Euclidian Algorithm
            b = a % b;
            a = temp;
        }
        result = a;
    }
 return result;
}


int getPeriod(t_matrix * sub_matrix) {
    int n = sub_matrix->nbrows;
    int *periods = (int *)malloc(n * sizeof(int)); //we allocate memory to store the period
    int period_count = 0;
    int cpt = 1;
    t_matrix * power_matrix = createEmptyMatrix(n); //multiplied matrix
    t_matrix * result_matrix = createEmptyMatrix(n); //final matrix
    copyMatrix(power_matrix, sub_matrix); //we put the data from the submatrix in the power matrix
    for (cpt = 1; cpt <= n; cpt++) {
        int diag_nonzero = 0;
        // Check if any diagonal element (data[i][i]) is positive and record the period if so
        for (int i = 0; i < n; i++) {
            if (power_matrix->data[i][i] > 0.0f) {
            diag_nonzero = 1;
            }
        }
        if (diag_nonzero) {
            periods[period_count] = cpt;
            period_count++;
        }
        power_matrix = multiplyMatrices(sub_matrix, result_matrix); // We needed to adapt this, as our multiply only takes 2 argument and return the result
        copyMatrix(power_matrix, result_matrix);
    }
    return gcd(periods, period_count); //return the greates common divisor of the periods and the number of period
} 