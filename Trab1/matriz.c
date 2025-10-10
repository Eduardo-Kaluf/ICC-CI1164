#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "matriz.h"
#include "vetor.h"


void alloc_single_matrix(real_t ***m, int n) {
    *m = alloc_single_vector(USE_CALLOC, sizeof(real_t *), n);

    for (int i = 0; i < n; ++i)
        (*m)[i] = alloc_single_vector(USE_CALLOC, sizeof(real_t *), n);
}

void free_matrix(real_t **m, int n) {
    if (m != NULL) {
        for (int i = 0; i < n; i++) {
            if (m[i] != NULL)
                free(m[i]);
        }

        free(m);
    }
}

void fill_zeros_matrix(real_t **m, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m[i][j] = 0.0;
}

void copy_matrix(real_t **A, real_t **B, int n){
    for (int i=0;i<n;i++) 
        memcpy(B[i], A[i], n * sizeof(real_t));
}

void print_matrix(real_t **m, int n) {
    for (int i = 0; i < n; i++) {
        printf("[ ");

        for (int j = 0; j < n; j++)
            printf("%.16g ", m[i][j]);

        printf("]\n");
    }

    printf("\n");
}

void sum_matrix(real_t **A, real_t **B, int n, real_t **C){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void matrix_times_scalar(real_t **A, int n, real_t value, real_t **dest) {
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            dest[i][j] = A[i][j] * value;
        }
    }
}

void matrix_times_vector(real_t **A, int n, real_t *V, real_t *dest) {

    fill_zeros_vector(dest, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dest[i] += A[i][j] * V[j];
}

void matrix_times_matrix(real_t **A, real_t **B, int n, real_t **C) {

    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            real_t s = 0.0;
            
            for (int k=0; k<n; k++) 
                s += A[i][k] * B[k][j];
            
            C[i][j] = s;
        }
    }
}
