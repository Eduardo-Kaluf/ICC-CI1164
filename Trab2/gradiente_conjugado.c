#include <math.h>
#include <stdio.h>

#include "gradiente_conjugado.h"
#include "csr_matriz.h"
#include "vetor.h"

#ifdef _LIK_
    #include <likwid.h>
#endif


real_t calc_gradiente_conjugado(csr * restrict c, real_t * restrict X, real_t * restrict M, rtime_t *tempo) {
    if (!c || !X || !M || !tempo)
        handle_error("Tentativa de acesso a um ponteiro nulo");

    real_t *X_old = alloc_single_vector(USE_CALLOC, sizeof(real_t), c->n);

    real_t *R = alloc_single_vector(USE_MALLOC, sizeof(real_t), c->n);
    copy_vector(R, c->B, c->n);

    real_t *V = alloc_single_vector(USE_MALLOC, sizeof(real_t), c->n);
    jacobi_times_vector(M, c->B, V, c->n);

    real_t *Y = alloc_single_vector(USE_MALLOC, sizeof(real_t), c->n);
    jacobi_times_vector(M, R, Y, c->n);

    real_t aux = dot_product(Y, R, c->n);

    real_t *Z = alloc_single_vector(USE_MALLOC, sizeof(real_t), c->n);

    *tempo = timestamp();

    int i;
    for (i = 0; i < MAX_IT; i++) {
        csr_time_vector(c, V, Z);

        real_t s = aux / dot_product(V, Z, c->n);

        sum_vector_times_scalar(V, c->n, s, X);

        sum_vector_times_scalar(Z, c->n, -s, R);

        jacobi_times_vector(M, R, Y, c->n);

        const real_t aux1 = dot_product(Y, R, c->n);

        const real_t m = aux1 / aux;

        aux = aux1;

        for (int j = 0; j < c->n; j++)
            V[j] = Y[j] + m * V[j];

        // na penultima iteração ele copia o vetor para calcular 
        // a norma do penultimo valor de X com o ultimo valor.
        if (i == MAX_IT - SECOND_LAST_IT)
            copy_vector(X_old, X, c->n);
    }

    // Média do tempo
    *tempo = (timestamp() - *tempo) / i;

    real_t norm = calc_norm (X, X_old, c->n);

    free(R); free(V); free(Z); free(Y); free(X_old);


    return norm;
}

real_t calc_norm(real_t *X, real_t *X_old, int n) {
    real_t norm_max = 0.0;

    for (int i = 0; i < n; i++) {
        real_t current_norm = fabs(X_old[i] - X[i]);
        if(current_norm <= __DBL_EPSILON__)
            return __DBL_EPSILON__;

        if (current_norm > norm_max)
            norm_max = current_norm;

    }

    return norm_max;
}
