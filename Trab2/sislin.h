#ifndef __SISLIN_H__
#define __SISLIN_H__

#include "utils.h"

typedef struct csr {
    real_t * values; 
    int *col_ind; 
    int *row_ptr;
    int n;
} csr; 

struct csr *alloc_csr (int n, int k);

/**
 * @brief Cria matriz 'A' k-diagonal (guardando-a em um vetor) e Termos independentes B
 *
 * @param A Vetor que guardará a k-diagonal a ser gerada
 * @param n Quantidade de linhas e colunas
 * @param B Vetor de termos independentes 
 * @param k Quantidade de diagonais 
 */
void criaKDiagonal(int n, int k, csr *A, real_t *B);

/**
 * @brief Gera matriz simetrica positiva 
 *
 * @param A Matriz k-diagonal
 * @param n Quantidade de linhas e colunas
 * @param B Vetor de termos independentes de A
 * @param k Quantidade de diagonais 
 * @param ASP Matriz simetrica positiva a ser gerada
 * @param bsp Vetor de termos independentes de ASP
 * @param tempo Ponteiro para variavel tempo
 */
void genSimetricaPositiva(real_t **A, real_t *B, int n, int k, real_t **ASP, real_t *bsp, rtime_t *tempo);

/**
 * @brief Separa a matriz A em triangular superior, inferior e diagonal 
 *
 * @param A Matriz k-diagonal
 * @param n Quantidade de linhas e colunas
 * @param k Quantidade de diagonais (sempre um número impar)
 * @param D Matriz Diagonal
 * @param L Matriz triangular inferior
 * @param U Matriz triangular superior
 * @param tempo Ponteiro para variavel tempo
 */
void geraDLU (real_t *A, int n, int k, real_t *D, real_t *L, real_t *U, rtime_t *tempo);

/**
 * @brief Gera a matriz inversa de pre-condicionadores
 *        baseado no valor de omega recebido (NONE, JACOBI, 
 *        SSOR, GAUSS-SEIDEL)
 *
 * @param n Quantidade de linhas e colunas
 * @param k Quantidade de diagonais 
 * @param D Matriz Diagonal
 * @param L Matriz triangular inferior
 * @param U Matriz triangular superior
 * @param w omega
 * @param M Matriz resultante (inversa de pre-condicionadores)
 * @param tempo Ponteiro para variavel tempo
 */
void geraPreCond(real_t **D, real_t **L, real_t **U, real_t w, int n, int k, real_t **M, rtime_t *tempo);

/**
 * @brief Calcula o residuo do sistema linear 
 *
 * @param A Matriz k-diagonal
 * @param B Vetor de termos independentes
 * @param X Vetor dos resultados
 * @param n Quantidade de linhas e colunas
 * @param k Quantidade de diagonais (sempre um número impar)
 * @param tempo Ponteiro para variavel tempo
 * 
 * @return Residuo
 */
real_t calcResiduoSL (real_t *A, real_t *B, real_t *X, int n, int k, rtime_t *tempo);

/**
 * @brief Calcula a matriz inversa de pré-condicionadores do metodo
 *        SSOR ou GAUSS-SEIDEL
 *
 * @param n Quantidade de linhas e colunas
 * @param D Matriz Diagonal
 * @param L Matriz triangular inferior
 * @param U Matriz triangular superior
 * @param w omega
 * @param M_inv Matriz resultante (inversa de pre-condicionadores)
 */
void ssor_Minv(real_t **L, real_t **U,real_t **D, int n, real_t w, real_t **M_inv);

#endif // __SISLIN_H__
