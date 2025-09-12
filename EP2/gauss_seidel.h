// EDUARDO KALUF - GRR 20241770

#ifndef __GAUSS_SEIDEL_EDO_H__
#define __GAUSS_SEIDEL_EDO_H__

#include "edo.h"

/**
 * @brief Resolve uma matrix tridiagonal pelo método de Gauss Seidel.
 *
 * @param sl Sistema linear tridiagonalizado.
 * @param Y Vetor solução do sistema.
 * @param maxiter A EDo que será usada para gerar uma tridiagonal.
 * @param norma A EDo que será usada para gerar uma tridiagonal.
 *
 * @return Quantidade de iterações que o algoritmo realizou.
 */
int gaussSeidel_3Diag(Tridiag *sl, real_t *Y, int maxiter, real_t *norma);

/**
 * @brief Calcula a normaL2 de uma matrix tridiagonal.
 *
 * @param sl Sistema linear tridiagonalizado.
 * @param Y Vetor solução do sistema.
 *
 * @return NormaL2 do resíduo.
 */
real_t normaL2_3Diag (Tridiag *sl, real_t *Y);

#endif // __GAUSS_SEIDEL_EDO_H__