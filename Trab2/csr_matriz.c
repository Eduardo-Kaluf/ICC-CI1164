#include <stdlib.h>
#include <stdio.h>

#include "csr_matriz.h"
#include "vetor.h"
#include "utils.h"


csr* alloc_csr(int n, int nnz_capacity) {
    csr *A = malloc(sizeof(csr));

    A->n = n;
    A->row_ptr = (int*)    malloc((n + 1)      * sizeof(int));
    A->col_ind = (int*)    malloc(nnz_capacity * sizeof(int));
    A->values  = (real_t*) malloc(nnz_capacity * sizeof(real_t));
    A->B       = (real_t*) malloc(n * sizeof(real_t));

    return A;
}

void print_csr(csr *c, enum MODE mode) {
    const int n = c->n;

    switch (mode) {
        case CSR_MODE:
            const int nnz = c->row_ptr[n];

            printf("values:  [");
            for (int i = 0; i < nnz; i++) {
                printf("%.16g", c->values[i]);

                if (i < nnz - 1)
                    printf(", ");
            }
            printf("]\n");

            printf("col_ind: [");
            for (int i = 0; i < nnz; i++) {
                printf("%d", c->col_ind[i]);

                if (i < nnz - 1)
                    printf(", ");
            }
            printf("]\n");

            printf("row_ptr: [");
            for (int i = 0; i <= n; i++) {
                printf("%d", c->row_ptr[i]);
                if (i < n) printf(", ");
            }

            printf("]\n");

            break;
        case STANDARD_MODE:
            for (int i = 0; i < n; i++) {
                const int row_start = c->row_ptr[i];
                const int row_end = c->row_ptr[i+1];

                int k = row_start;

                for (int j = 0; j < n; j++) {
                    if (k < row_end && c->col_ind[k] == j) {
                        printf("%.16g ", c->values[k]);
                        k++;
                    } else
                        printf("%.16g ", 0.0);
                }

                printf("\n");
            }

            break;
        default:
            break;
    }

    printf("\n");
    print_vector(c->B, c->n);
    printf("\n");
}

csr* csr_transpose(const csr *c) {

    int n = c->n;
    int nnz = c->row_ptr[n];

    csr *c_out = alloc_csr(n, nnz);

    int *temp_counts = calloc(n, sizeof(int));

    for (int k = 0; k < nnz; k++) {
        int j_col = c->col_ind[k];
        temp_counts[j_col]++;
    }

    c_out->row_ptr[0] = 0;
    for (int i = 0; i < n; i++)
        c_out->row_ptr[i+1] = c_out->row_ptr[i] + temp_counts[i];

    for (int i = 0; i < n; i++)
        temp_counts[i] = c_out->row_ptr[i];

    for (int i = 0; i < n; i++) {
        for (int k = c->row_ptr[i]; k < c->row_ptr[i+1]; k++) {

            real_t val = c->values[k];
            int j_col = c->col_ind[k];

            int dest_index = temp_counts[j_col];

            c_out->values[dest_index] = val;
            c_out->col_ind[dest_index] = i;

            temp_counts[j_col]++;
        }
    }

    c_out->B = c->B;

    free(temp_counts);
    return c_out;
}

void csr_time_vector(csr *c, real_t *X, real_t *Y) {
    for (int i = 0; i < c->n; i++) {
        double sum = 0.0;

        int row_start = c->row_ptr[i];
        int row_end = c->row_ptr[i+1];

        for (int k = row_start; k < row_end; k++) {

            int j = c->col_ind[k];

            double value = c->values[k];

            sum += value * X[j];
        }

        Y[i] = sum;
    }
}
