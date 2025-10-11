#ifndef __GRADIENTE_CONJUGADO_H__
#define __GRADIENTE_CONJUGADO_H__

#include "utils.h"

/**
 * @brief Calculo do metodo do gradiente conjulgado
 *
 * @param A Matriz transposta
 * @param B Vetor termos independentes 
 * @param X Vetor resultado do sistema
 * @param M Matriz inversa de pre condicionadores
 * @param n Quantidade de linhas e colunas
 * @param maxit Maximo de iterações
 * @param episilon Tolerancia da norma
 * @param tempo Ponteiro para a varivel tempo 
 *              (guarda o tempo medio das iterações)
 * 
 * @return norma maxima 
 */
real_t calc_gradiente_conjugado(real_t **A, real_t *B, real_t *X, real_t **M, int n, int maxit, real_t epsilon, rtime_t *tempo);

/**
 * @brief calcula a norma maxima
 *
 * @param X Novo vetor calculado
 * @param X_old Vetor da iteração anterior
 * @param n Tamanho do vetor
 * 
 * @return norma maxima entre os vetores
 */
real_t calc_norm(real_t *X, real_t *X_old, int n);

#endif // __GRADIENTE_CONJUGADO_H__
