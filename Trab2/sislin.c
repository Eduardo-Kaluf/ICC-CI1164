#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "csr_matriz.h"
#include "sislin.h"
#include "utils.h"


static inline real_t generateRandomA(unsigned int i, unsigned int j, unsigned int k);

static inline real_t generateRandomB(unsigned int k);

/**
 * Função que gera os coeficientes de um sistema linear k-diagonal
 * @param i,j coordenadas do elemento a ser calculado (0<=i,j<n)
 * @param k Numero de diagonais da matriz A
 */
static inline real_t generateRandomA(unsigned int i, unsigned int j, unsigned int k) {
    static real_t invRandMax = 1.0 / (real_t)RAND_MAX;
    return ( (i==j) ? (real_t)(k<<1) : 1.0 )  * (real_t)random() * invRandMax;
}

/**
 * Função que gera os termos independentes de um sistema linear k-diagonal
 * @param k Numero de diagonais da matriz A
 */
static inline real_t generateRandomB(unsigned int k ) {
    static real_t invRandMax = 1.0 / (real_t)RAND_MAX;
    return (real_t)(k<<2) * (real_t)random() * invRandMax;
}


/* Cria matriz 'A' k-diagonal e Termos independentes B */
void criaKDiagonal(csr *c) {
    if (!c || !c->values || !c->col_ind || !c->row_ptr)
        handle_error("Tentativa de acesso a um ponteiro nulo");

    c->row_ptr[0] = 0;

    int nnz_count = 0;

    for (int i = 0; i < c->n; i++) {

        for (int j = max(0, i - BAND_WIDTH); j <= min(c->n - 1, i + BAND_WIDTH); j++) {

            c->values[nnz_count] = generateRandomA(i, j, K);
            c->col_ind[nnz_count] = j;

            nnz_count++;
        }

        c->row_ptr[i + 1] = nnz_count;
    }

    for (int i = 0; i < c->n; i++)
        c->B[i] = generateRandomB(K);

}

/* Gera matriz simetrica positiva */
csr* genSimetricaPositiva(csr *c, rtime_t *tempo) {
    if (!c || !tempo)
        handle_error("Tentativa de acesso a um ponteiro nulo");

    *tempo = timestamp();

    csr *CT = csr_transpose(c);

    const int n = CT->n;

    const int nnz_capacity = n * SP_K - SP_OFF_SET;

    csr *c_out = alloc_csr(n, nnz_capacity);

    c_out->row_ptr[0] = 0;
    c_out->n = n;
    int counter = 0;
    for (int i = 0; i < n; i++) {
        const int row_start = CT->row_ptr[i];
        const int row_end = CT->row_ptr[i+1];

        c_out->row_ptr[i + 1] = c_out->row_ptr[i];

        for (int j = 0; j < n; j++) {
            const int row_start2 = CT->row_ptr[j];
            const int row_end2 = CT->row_ptr[j+1];

            real_t sum = 0;
            for (int h = row_start, l = row_start2; h < row_end && l < row_end2;) {
                if (CT->col_ind[h] == CT->col_ind[l]) {
                    sum += CT->values[h] * CT->values[l];
                    l++;
                    h++;
                }
                else if (CT->col_ind[h] > CT->col_ind[l])
                    l++;
                else
                    h++;
            }

            if (sum != 0) {
                c_out->row_ptr[i + 1] += 1;
                c_out->values[counter] = sum;
                c_out->col_ind[counter] = j;
                counter++;
            }
        }
    }

    csr_time_vector(CT, CT->B, c_out->B);

    *tempo = timestamp() - *tempo;

    return c_out;
}


void geraCondicionadorJacobi(csr *c, real_t *M, rtime_t *tempo) {
    if (!c || !M || !tempo)
        handle_error("Tentativa de acesso a um ponteiro nulo");

    *tempo = timestamp();

    // Pré-condicionador de Jacobi
    for (int i = 0; i < c->n; i++) {
        for (int j = c->row_ptr[i]; j < c->row_ptr[i + 1]; j++) {

            if (c->col_ind[j] == i) {

                const real_t diagonal_value = c->values[j];

                printf("%f", diagonal_value);

                if (diagonal_value != 0)
                    M[i] = 1 / diagonal_value;
                else
                    handle_error("Determinante da matriz é zero, impossível gerar pré-condicionador");

                break;
            }
        }
    }

    *tempo = timestamp() - *tempo;
}

// TODO TODO TODO OPTIMAZE THIS
real_t calcResiduoSL(csr *c, real_t *X, rtime_t *tempo) {
    if (!c || !X || !tempo)
        handle_error("Tentativa de acesso a um ponteiro nulo");

    // *tempo = timestamp();
    //
    // int band_size = k / 2;
    // real_t norm = 0.0;
    //
    // real_t *r = alloc_single_vector(USE_MALLOC, sizeof(real_t), n);
    // copy_vector(r, B, n);
    //
    //
    // //
    // for (int i = 0; i < n; i++)
    //     for(int j = 0; j < band_size; j++)
    //         r[i] -= A[i + (j * n)] * X[j];
    //
    // // // Lower part of the matrix
    // // for (int i = 0; i < n; i++)
    // //     for (int j = i - 1; j >= i - band_size && j >= 0; j--)
    // //         r[i] -= A[i][j] * X[j];
    //
    // // Diagonal
    // for (int i = 0; i < n; i++)
    //     r[i] -= A[i + (n * band_size)] * X[i];
    //
    //
    // //i is the row and j the line
    // for (int i = 0; i < n; i++)
    //     for(int j = 0; j < band_size; j++)
    //         r[i] -= A[(n * (band_size + 1)) + i + (j * n)] * X[j];
    // // // Upper part of the matrix
    // // for (int i = 0; i < n; i++)
    // //     for (int j = i + 1; j <= band_size + i && j < n; j++)
    // //         r[i] -= A[i][j] * X[j];
    //
    // for (int i = 0; i < n; i++)
    //     norm += r[i] * r[i];
    //
    // norm = sqrt(norm);
    //
    // free(r);
    //
    // *tempo = timestamp() - *tempo;
    //
    // return norm;

    // MOCK
    return 2.0;
}
