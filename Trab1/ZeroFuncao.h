#ifndef __ZEROFUNCAO_H__
#define __ZEROFUNCAO_H__

#include <float.h>
#include "utils.h"

// Aproximação aceitável como valor zero
#define ZERO DBL_EPSILON

// Parâmetros para teste de convergência
#define MAXIT 600
#define EPS 1.0e-7
#define ULPS 3

typedef struct {
  real_t *p;
  int grau;
} Polinomio;

// Métodos
// Retornam valor do erro quando método finalizou. Este valor depende de tipoErro

real_t newtonRaphson (Polinomio p, real_t x0, enum CriteriosDeParada criterioParada, int *it, real_t *raiz, enum CalcType calcType);
real_t bisseccao (Polinomio p, real_t a, real_t b, enum CriteriosDeParada criterioParada, int *it, real_t *raiz, enum CalcType calcType);

// Cálculo de Polinômios
void calcPolinomio(Polinomio p, real_t x, real_t *px, real_t *dpx, enum CalcType calcType);

bool getCriterioDeParada(enum CriteriosDeParada criterioParada, real_t x_old, real_t x_new, real_t fx, real_t *error);

#endif // __ZEROFUNCAO_H__

