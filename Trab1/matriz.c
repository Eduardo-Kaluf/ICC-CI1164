#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "matriz.h"


void alloc_single_matrix(real_t ***m, int n) {
    *m = calloc(n, sizeof(real_t *));
    if (!(*m)) {
        fprintf(stderr, "Failed malloc!\n");
        return;
    }

    for (int i = 0; i < n; ++i) {
        (*m)[i] = calloc(n, sizeof(real_t));

        if (!(*m)[i]) {
            fprintf(stderr, "Failed malloc!\n");

            for (int j = 0; j < i; j++)
                free((*m)[j]);
            free(*m);

            return;
        }
    }
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

void matrix_times_vector(real_t **m, int n, real_t *v, real_t *rv) {

    fill_zeros_vector(rv, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            rv[i] += m[i][j] * v[j];
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
