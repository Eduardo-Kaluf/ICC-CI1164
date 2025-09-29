#include "gradiente_conjugado.h"

#include <string.h>
#include "sislin.h"

void calc_gradiente_conjugado(real_t **A, real_t *B, real_t *X, int n, int k, real_t w, int maxit, double epsilon) {
    int size = n * sizeof(real_t);
    rtime_t tempo;
    real_t **M = malloc(n * n * sizeof(real_t));

    // TODO REMOVE NULL LATER WHEN MORE PRECONDITIONERS ARE ADDED
    geraPreCond(NULL, NULL, NULL, w, n, k, M, &tempo);

    fill_zeros_vector(X, n);

    real_t *R = malloc(size);
    memcpy(R, B, size);

    real_t *V = malloc(n * sizeof(real_t));
    matrix_times_vector(M, n, B, V);

    real_t *Y = malloc(n * sizeof(real_t));
    matrix_times_vector(M, n, R, Y);

    real_t aux = dot_product(Y, R, n);


    real_t *Z = malloc(n * sizeof(real_t));
    for (int i = 0; i < maxit; i++) {

        matrix_times_vector(A, n, V, Z);
        real_t s = aux / dot_product(V, Z, n);

        for (int j = 0; j < n; j++)
            X[j] += s * V[j];

        for (int j = 0; j < n; j++)
            R[j] -= s * Z[j];

        matrix_times_vector(M, n, R, Y);

        if (dot_product(R, R, n) < epsilon)
            return;

        real_t aux1 = dot_product(Y, R, n);

        real_t m = aux1 / aux;

        aux = aux1;

        for (int j = 0; j < n; j++)
            V[j] = Y[j] + m * V[j];
    }

    free(R);
    free(V);
    free(Z);
    free(Y);
    free(M);
}