// EDUARDO KALUF - GRR 20241770

#ifndef FATORACAO_LU_H
#define FATORACAO_LU_H
#include "edo.h"


/**
 * @brief Aplica o método da fatoração LU em uma tridiagonal para separa-lás em LOWER e UPPER,
 *        guardando todos os valores da fatoração na própria tridiagonal.
 * @param tridiag A matriz tridiagonal a ser fatorada.
 * @param n O tamanho da matriz tridiagonal.
 */
void fatoracaoLu(Tridiag *tridiag, int n);

/**
 * @brief Resolve uma matriz tridiagonal que esteja na forma LU.
 *
 * @param tridiag A matriz tridiagonal a resolvida.
 * @param X Um vetor de coeficientes onde a resposta será armazenada.
 */
void resolveSl(Tridiag *tridiag, double *X);

#endif //FATORACAO_LU_H
