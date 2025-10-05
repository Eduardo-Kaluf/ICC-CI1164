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
 * @param k numero de diagonais da matriz A
 */
static inline real_t generateRandomA(unsigned int i, unsigned int j, unsigned int k) {
    static real_t invRandMax = 1.0 / (real_t)RAND_MAX;
    return ( (i==j) ? (real_t)(k<<1) : 1.0 )  * (real_t)random() * invRandMax;
}

/**
 * Função que gera os termos independentes de um sistema linear k-diagonal
 * @param k numero de diagonais da matriz A
 */
static inline real_t generateRandomB(unsigned int k ) {
    static real_t invRandMax = 1.0 / (real_t)RAND_MAX;
    return (real_t)(k<<2) * (real_t)random() * invRandMax;
}


// B ANTES ERA UM PONTEIRO DE PONTEIROS (**B) ??????

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


// A ANTES ERA UM PONTEIRO APENAS (*A) ????

/* Gera matriz simetrica positiva */
void genSimetricaPositiva(real_t **A, real_t *b, int n, int k, real_t **ASP, real_t *bsp, rtime_t *tempo) {
    *tempo = timestamp();

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


    // ASP should be A^t * A
    // bsp should be A^t * B
    // where A^t is the transposed A matrix

    *tempo = timestamp() - *tempo;
}

// TODO, VER SE ZERAR A MATRIZ DEVE CONTAR COMO TEMPO DE EXECUÇÃO OU NÃO
// A ANTES ERA UM PONTEIRO APENAS (*A) ????

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
void geraPreCond(real_t *D, real_t *L, real_t *U, real_t w, int n, int k, real_t **M, rtime_t *tempo) {
    fill_zeros_matrix(M, n);

    *tempo = timestamp();

    switch (w) {
        case -1.0:
            // sem pré-condicionador

            generate_identity(M, n);

            break;
        case 0.0:
            // pré-condicionador de Jacobi

            for (int i = 0; i < n; i++) {
                if (D[i] != 0)
                    M[i][i] = 1 / D[i];
                else
                    break; // RETORNAR ALGUM TIPO DE ERRO (DETERMINANTE DA MATRIZ É 0 E PORTANTO NÃO POSSUI INVERSA)
            }

            break;
        case 1.0:
            // pré-condicionador de Gauss-Seidel
            break;
        default:
            // pré-condicionador SSOR
    }

      *tempo = timestamp() - *tempo;
}


// A ANTES ERA UM PONTEIRO APENAS (*A) ????
// ANTES A FUNÇÃO NÃO RETORNAVA UM PONTEIRO (real_t calcResiduoSL) ?????

real_t *calcResiduoSL(real_t **A, real_t *b, real_t *X, int n, int k, rtime_t *tempo) {
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
        r[i] -= A[i][i] * X[j];

    *tempo = timestamp() - *tempo;

    return r;
}
