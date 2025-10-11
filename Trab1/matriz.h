#ifndef __MATRIZ_H__
#define __MATRIZ_H__

#include "utils.h"

/**
 * @brief Aloca uma matriz fazendo as verificações de segurança necessárias
 *
 * @param m Matriz a ser alocada
 * @param n Quantidade de linhas e colunas
 *
 */
void alloc_single_matrix(real_t ***m, int n);

/**
 * @brief Desaloca uma matriz 
 *
 * @param m Matriz a ser alocada
 * @param n Quantidade de linhas e colunas (nxn)
 *
 */
void free_matrix(real_t **m, int n);

/**
 *
 *  @brief Preenche um vetor inteiro com zeros
 *
 *  @param m matriz
 *  @param n Quantidade de linhas e colunas
 */
void fill_zeros_matrix(real_t **m, int n);

/**
 *
 *  @brief Copia uma matriz para outra 
 *
 *  @param A matriz original a ser copiada
 *  @param dest matriz copia  
 *  @param n Quantidade de linhas e colunas
 */
void copy_matrix(real_t **A, real_t **dest, int n);

/**
 * @brief Exibe a matriz na tela com format "%.16g"
 *
 * @param m matriz
 * @param n Quantidade de linhas e colunas
 */
void print_matrix(real_t **m, int n);

/**
 * @brief Soma duas matrizes 
 *
 * @param A Primeira matriz a ser somada
 * @param B Segunda matriz a ser somada
 * @param dest matriz resultado
 * @param n Quantidade de linhas e colunas
 */
void sum_matrix (real_t **A, real_t **B, int n, real_t **dest);

/**
 * @brief Multiplica uma matriz por um valor escalar 
 *
 * @param A Matriz original
 * @param value valor escalar 
 * @param dest matriz resultado
 * @param n Quantidade de linhas e colunas
 */
void matrix_times_scalar(real_t **A, int n, real_t value, real_t **dest);

/**
 * @brief Multiplica uma matriz por um vetor 
 *
 * @param A Matriz original
 * @param v vetor 
 * @param rv vetor resultado
 * @param n Tamanho do vetor e 
 *          Quantidade de linhas e colunas da matriz
 */
void matrix_times_vector(real_t **m, int n, real_t *v, real_t *rv);

/**
 * @brief Multiplica uma matriz por uma matriz
 *
 * @param A Primeira matriz operando
 * @param B Segunda matriz operando 
 * @param dest matriz resultado
 * @param n Quantidade de linhas e colunas
 */
void matrix_times_matrix(real_t **A, real_t **B, int n, real_t **dest);

#endif // __MATRIZ_H__
