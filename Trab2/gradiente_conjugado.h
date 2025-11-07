#ifndef __GRADIENTE_CONJUGADO_H__
#define __GRADIENTE_CONJUGADO_H__

#include "csr_matriz.h"
#include "utils.h"


/**
 * @brief Calculo do metodo do gradiente conjulgado
 *
 * @param c Matriz k-diagonal guardada como CSR
 * @param X Vetor resultado do sistema
 * @param M Matriz inversa do pre condicionador JACOBI
 * @param tempo Ponteiro para a varivel tempo (guarda o tempo medio das iterações)
 * 
 * @return Norma maxima
 */
real_t calc_gradiente_conjugado(csr *c, real_t *X, real_t *M, rtime_t *tempo) ;

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
