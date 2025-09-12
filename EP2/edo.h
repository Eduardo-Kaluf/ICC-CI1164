// EDUARDO KALUF - GRR 20241770

#ifndef __EQDIFF_H__
#define __EQDIFF_H__

#define FORMAT "%23.15e"

#include "utils.h"

// Sistema linear Tri-diagonal
typedef struct {
  real_t *D, *Di, *Ds, *B;
  int n;
} Tridiag;

// Equação Diferencial Ordinária
typedef struct {
  int n; // número de pontos internos na malha
  real_t a, b; // intervalo
  real_t ya, yb; // condições contorno
  real_t p, q, r1, r2, r3, r4; // coeficientes EDO genérica
} EDo;

/**
 * @brief Lê da entrada padrão uma EDo que o usuário passar.
 *
 *  Ordem de leitura:
 *      1ª linha: quantidade de pontos da malha da EDO;
 *      2ª linha: intervalo a e b onde a EDO é válida;
 *      3ª linha: os valores de contorno  y(a) e y(b);
 *      4ª linha: os coeficientes p e q da EDO genérica;
 *      5ª linha em diante: uma ou mais linhas contendo os coeficientes r1, r2, r3  e r4 da definição da função r(x).
 *
 * @return Uma struct EDo populada com as informações do usuário
 */
EDo* read_edo();

/**
 * @brief Exibe um SL na saída padrão a partir de uma EDo.
 *
 * @param edoeq A EDo que será exibida no formato de matrix tridiagonal
 */
void prnEDOsl (EDo *edoeq);

/**
 * @brief Gera uma tridiagonal a partir de uma EDo.
 *
 * @param edoeq A EDo que será usada para gerar uma tridiagonal.
 * @return A struct da matrix tridiagonal gerada
*/
Tridiag *genTridiag (EDo *edoeq);

/**
 * @brief Libera a tridiagonal e seus componentes.
*/
void free_tridiag(Tridiag *tridiag);

#endif // __EQDIFF_H__

