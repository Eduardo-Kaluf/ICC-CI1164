#include <stdio.h>
#include <stdlib.h>    /* for exit e random/srandom */
#include <string.h>
#include <math.h>

#include "utils.h"
#include "sislin.h"

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
void criaKDiagonal(int n, int k, real_t **A, real_t *B) {
    fill_zeros_matrix(A, n);

    int band_size = k / 2;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j <= band_size + i && j < n; j++)
            A[i][j] = generateRandomA(i, j, k);

    for (int i = 0; i < n; i++)
        for (int j = i - 1; j >= i - band_size && j >= 0; j--)
            A[i][j] = generateRandomA(i, j, k);

    for (int i = 0; i < n; i++) {
        A[i][i] = generateRandomA(i, i, k);
        B[i] = generateRandomB(k);
    }
}

/* Gera matriz simetrica positiva */
void genSimetricaPositiva(real_t **A, real_t *b, int n, int k, real_t **ASP, real_t *bsp, rtime_t *tempo) {
    *tempo = timestamp();

    // ASP should be A^t * A
    // bsp should be A^t * B
    // where A^t is the transposed A matrix

    // TODO SEE WHAT'S BETTER, JUST INVERT THE INDEXES TO ACHIEVE THE TRANSPOSE OR ACTUALLY CALCULATE A TRANSPOSED MATRIX TO MAXIMIZE CACHE USAGE
    // TODO STILL NEED TO FINISH THIS FUNCTION

    fill_zeros_matrix(ASP, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int h = 0; h < n; h++)
                ASP[i][j] += A[h][i] * A[h][j];

    fill_zeros_vector(bsp, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            bsp[i] += A[j][i] * b[j];

    *tempo = timestamp() - *tempo;
}

// K IS ALWAYS A ODD NUMBER
void geraDLU(real_t **A, int n, int k, real_t **D, real_t **L, real_t **U, rtime_t *tempo) {
    fill_zeros_matrix(D, n);
    fill_zeros_matrix(L, n);
    fill_zeros_matrix(U, n);

    *tempo = timestamp();

    int band_size = k / 2;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j <= band_size + i && j < n; j++)
            U[i][j] = A[i][j];

    for (int i = 0; i < n; i++)
        for (int j = i - 1; j >= i - band_size && j >= 0; j--)
            L[i][j] = A[i][j];

    for (int i = 0; i < n; i++)
        D[i][i] = A[i][i];

    *tempo = timestamp() - *tempo;
}

/**
 * Devolve matriz M⁻¹
 *
 */
void geraPreCond(real_t **D, real_t **L, real_t **U, real_t w, int n, int k, real_t **M, rtime_t *tempo) {
    fill_zeros_matrix(M, n);

    *tempo = timestamp();

    if (w == -1.0)
        generate_identity(M, n); // sem pré-condicionador
    else if (w == 0.0) {
        for (int i = 0; i < n; i++) { // pré-condicionador de Jacobi
            if (D[i][i] != 0)
                M[i][i] = 1 / D[i][i];
            else
                break; // RETORNAR ALGUM TIPO DE ERRO (DETERMINANTE DA MATRIZ É 0 E PORTANTO NÃO POSSUI INVERSA)
        }
    }
    else {
        return;
        // pré-condicionador de Gauss-Seidel / pré-condicionador SSOR
    }

    *tempo = timestamp() - *tempo;
}


// TODO VERIFICAR SE ESTA FUNÇÃO DEVE RETORNAR A NORMA OU O VETOR RESIDUAL
real_t calcResiduoSL(real_t **A, real_t *b, real_t *X, int n, int k, rtime_t *tempo) {
    *tempo = timestamp();

    int b_size = n * sizeof(real_t);

    real_t *r = malloc(b_size);

    memcpy(r, b, b_size);

    int band_size = k / 2;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j <= band_size + i && j < n; j++)
            r[i] -= A[i][j] * X[j];

    for (int i = 0; i < n; i++)
        for (int j = i - 1; j >= i - band_size && j >= 0; j--)
            r[i] -= A[i][j] * X[j];

    for (int i = 0; i < n; i++)
        r[i] -= A[i][i] * X[i];


    real_t norm = 0.0;

    for (int i = 0; i < n; i++)
        norm += r[i] * r[i];


    norm = sqrt(norm);

    free(r);

    *tempo = timestamp() - *tempo;

    return norm;
}
