#ifndef __SISLIN_H__
#define __SISLIN_H__

#include "utils.h"
#include "csr_matriz.h"


/**
 * @brief Cria matriz 'c' k-diagonal (guardando-a em um vetor) e seus termos independentes B
 *
 * @param c Matriz k-diagonal guardada como CSR
 */
void criaKDiagonal(csr *c);

/**
 * @brief Gera matriz simetrica positiva 
 *
 * @param c Matriz k-diagonal guardada como CSR
 * @param tempo Ponteiro para variavel tempo
 *
 * @return Matriz simétrica positiva
 */
csr* genSimetricaPositiva(csr *c, rtime_t *tempo);


/**
 * @brief Gera a matriz inversa do pre-condicionadore de JACOBI
 *
 * @param c Matriz k-diagonal guardada como CSR
 * @param M Matriz resultante (inversa de pre-condicionadores)
 * @param tempo Ponteiro para variavel tempo
 */
void geraCondicionadorJacobi(csr *c, real_t *M, rtime_t *tempo);

/**
 * @brief Calcula o residuo do sistema linear 
 *
 * @param c Matriz k-diagonal guardada como CSR
 * @param X Vetor dos resultados
 * @param tempo Ponteiro para variavel tempo
 * 
 * @return Residuo
 */
real_t calcResiduoSL(csr *c, real_t *X, rtime_t *tempo);

#endif // __SISLIN_H__
