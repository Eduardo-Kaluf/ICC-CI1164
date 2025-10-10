#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "matriz.h"
#include "sislin.h"
#include "utils.h"
#include "vetor.h"


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

    // Calcula a matriz ASP (A^T * A), aproveitando a estrutura k-diagonal
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) { // Itera apenas sobre a parte superior da matriz
            ASP[i][j] = 0.0;
            
            // Define o intervalo de h onde A[h][i] e A[h][j] podem ser não nulos
            int h_start = (int) fmax(0, fmax(i - k, j - k));
            int h_end = (int) fmin(n, fmin(i + k + 1, j + k + 1));
            
            for (int h = h_start; h < h_end; h++) {
                ASP[i][j] += A[h][i] * A[h][j];
            }

            // Atribui o valor à parte inferior, por simetria
            if (i != j) {
                ASP[j][i] = ASP[i][j];
            }
        }
    }
    
    //multiplica pela transposta
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            bsp[i] += A[j][i] * b[j];

    *tempo = timestamp() - *tempo;
}

// K IS ALWAYS A ODD NUMBER
void geraDLU(real_t **A, int n, int k, real_t **D, real_t **L, real_t **U, rtime_t *tempo) {
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
    *tempo = timestamp();

    if (w == -1.0) {
        // Sem pré-condicionador

        for (int i = 0; i < n; i++)
            M[i][i] = 1.0;
    }
    else if (w == 0.0) {
        // Pré-condicionador de Jacobi

        for (int i = 0; i < n; i++) {
            if (D[i][i] != 0)
                M[i][i] = 1 / D[i][i];
            else
                handle_error("Determinante da matriz é zero, impossível gerar pré-condicionador");
        }
    }
    else {
        // pré-condicionador de Gauss-Seidel / pré-condicionador SSOR
        ssor_Minv(L, U, D, n, k, w, tempo, M);
    }

    *tempo = timestamp() - *tempo;
}

real_t calcResiduoSL(real_t **A, real_t *b, real_t *X, int n, int k, rtime_t *tempo) {
    *tempo = timestamp();

    int band_size = k / 2;
    real_t norm = 0.0;

    real_t *r = alloc_single_vector(USE_MALLOC, sizeof(real_t), n);
    memcpy(r, b, n * sizeof(real_t));

    // Upper part of the matrix
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j <= band_size + i && j < n; j++)
            r[i] -= A[i][j] * X[j];

    // Lower part of the matrix
    for (int i = 0; i < n; i++)
        for (int j = i - 1; j >= i - band_size && j >= 0; j--)
            r[i] -= A[i][j] * X[j];

    // Diagonal
    for (int i = 0; i < n; i++)
        r[i] -= A[i][i] * X[i];

    for (int i = 0; i < n; i++)
        norm += r[i] * r[i];

    norm = sqrt(norm);

    free(r);

    *tempo = timestamp() - *tempo;

    return norm;
}

void invert_lower (real_t **L, real_t **L_inv, int n){

    fill_zeros_matrix(L_inv, n);
    for(int c = 0; c < n; ++c){
        for(int i = 0; i < n; ++i) {
            real_t s = (i==c) ? 1.0 : 0.0;

            for (int j = 0; j < i; ++j) 
                s -= L[i][j] * L_inv[j][c];

            L_inv[i][c] = s / L[i][i];
        }
        
    }
}

void invert_upper (real_t **U, real_t **U_inv, int n) {
    
    fill_zeros_matrix(U_inv, n);
    for(int c = 0; c < n; ++c){
        for (int i = n-1; i >= 0; --i) {
            real_t s = (i==c) ? 1.0 : 0.0;

            for (int j = i+1; j < n; ++j) 
                s -= U[i][j] * U_inv[j][c];
            
            U_inv[i][c] = s / U[i][i];
        }
    }
}

//seria melhor se recebesse a matriz A completa
void ssor_Minv(real_t **L, real_t **U,real_t **D, int n, int k, real_t w, rtime_t *tempo, real_t **M_inv){
    real_t **AL, **AU;
    //nao seria melhor isso retornar uma matriz?
    alloc_single_matrix(&AL, n);
    alloc_single_matrix(&AU, n);

    copy_matrix(AL, L, n);
    copy_matrix(AU, U, n);

    //TODO melhorar essas funções para K diagonais
    matrix_times_scalar(AL, n, w, AL);
    matrix_times_scalar(AU, n, w, AU);

    sum_matrix(AL, D, n, AL);
    sum_matrix(AU, D, n, AU);

    // calculando as inversas
    real_t **AL_inv, **AU_inv;
    alloc_single_matrix(&AL_inv, n);
    alloc_single_matrix(&AU_inv, n);

    invert_lower(AL, AL_inv, n);
    invert_upper(AU, AU_inv, n);

    real_t **temp;
    alloc_single_matrix(&temp, n);

    matrix_times_matrix(AU_inv, D, n, temp);

    matrix_times_matrix(temp, AL_inv, n, M_inv);

    free_matrix(AL, n);
    free_matrix(AU, n);
    free_matrix(AL_inv, n);
    free_matrix(AU_inv, n);
    free_matrix(temp, n);
}

