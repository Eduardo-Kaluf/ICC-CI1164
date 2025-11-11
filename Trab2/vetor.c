#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "vetor.h"



void jacobi_times_vector(real_t *M, real_t *X, real_t *V, int n) {
    if (!M || !X)
        handle_error("Tentativa de acesso a um ponteiro nulo");

    for (int i = 0; i < n; i++)
        V[i] = M[i] * X[i];
}


real_t dot_product(real_t *v1, real_t *v2, int n) {
    if (!v1 || !v2)
        handle_error("Tentativa de acesso a um ponteiro nulo");

    real_t sum = 0.0;

    for (int i = 0; i < n; i++)
        sum += v1[i] * v2[i];

    return sum;
}

void print_vector(real_t *v, int n) {
    if (!v)
        handle_error("Tentativa de acesso a um ponteiro nulo");

    for (int i = 0; i < n; i++)
        printf("%.16g ", v[i]);

    printf("\n");
}

void sum_vector_times_scalar(real_t *v, int n, real_t value, real_t *dest) {
    if (!v || !dest)
        handle_error("Tentativa de acesso a um ponteiro nulo");

    for (int i = 0; i < n; i++)
        dest[i] += value * v[i];
}

void copy_vector(real_t *dest, real_t *src, int n) {
    if (!dest || !src)
        handle_error("Tentativa de acesso a um ponteiro nulo");

    memcpy(dest, src, n * sizeof(real_t));
}

void* alloc_single_vector(enum ALLOC_TYPE type, int size, int n) {
    void* ptr = NULL;
    int total_size = n * size;

    switch (type) {
        case USE_MALLOC:
            ptr = malloc(total_size);
            break;
        case USE_CALLOC:
            ptr = calloc(n, size);
            break;
        default:
            handle_error("Tipo de alocação inválida.\n");
    }

    if (ptr == NULL && total_size > 0)
        handle_error("Erro na alocação de memória.\n");

    return ptr;
}
