#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "sislin.h"
#include "gauss_seidel.h"

// Método de Gauss-Seidel clássico
int gauss_seidel (linear_system_t *C, real_t *X, real_t error, int max_iterations, real_t *norm) {
    real_t *X_old = calloc(C->n, sizeof(real_t));

    for (int i = 0; i < C->n; ++i)
        X[i] = 0;

    int it = 0;
    for (; it < max_iterations; ++it) {

        for (int i = 0; i < C->n; ++i) {

            real_t sigma = 0;

            for (int j = 0; j < C->n; ++j) {
                if (i != j)
                    sigma += C->A[i][j] * X[j];
            }

            X[i] = (C->b[i] - sigma) / C->A[i][i];
        }

        *norm = normMax(X, X_old, C->n);
        if (*norm < error)
            break;

        for (int i = 0; i < C->n; ++i)
            X_old[i] = X[i];
    }

    free(X_old);

    return it;
}
