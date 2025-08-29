#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "sislin.h"
#include "eliminacao_gauss.h"

static int encontraMax(linear_system_t *C, int line) {
    real_t max = ABS(C->A[line][line]);
    int pivot_line = line;

    for (int i = line + 1; i < C->n; i++) {
        if (ABS(C->A[i][line]) > max) {
            max = C->A[i][line];
            pivot_line = i;
        }
    }

    return pivot_line;
}

static void trocaLinha(linear_system_t *C, int k, int pivot_line) {
    // SWITCH TO MEMORY SWAP INSTEAD OF LOOP
    real_t temp;

    for (int i = 0; i < C->n; i++) {
        temp = C->A[k][i];
        C->A[k][i] = C->A[pivot_line][i];
        C->A[pivot_line][i] = temp;
    }

    temp = C->b[k];
    C->b[k] = C->b[pivot_line];
    C->b[pivot_line] = temp;
}

void lower_triangularization(linear_system_t *C) {

    for (int i=0; i < C->n; ++i) {

        int pivot_line = encontraMax(C, i);

        if ( i != pivot_line )
            trocaLinha(C, i, pivot_line);

        for (int k = i + 1; k < C->n; ++k) {
            double m = (C->A)[k][i] / (C->A)[i][i];

            C->A[k][i] = 0.0;

            for(int j=i+1; j < C->n; ++j)
                C->A[k][j] -= C->A[i][j] * m;

            C->b[k] -= (C->b)[i] * m;
        }
    }
}

void backward_substitution(linear_system_t *C, real_t *X) {
    for (int i = C->n - 1; i >= 0; --i) {
        X[i] = C->b[i];

        for (int j = i + 1; j < C->n; ++j)
            X[i] -= C->A[i][j] * X[j];

        X[i] /= C->A[i][i];
    }
}
