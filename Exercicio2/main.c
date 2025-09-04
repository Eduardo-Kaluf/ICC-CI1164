#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "utils.h"
#include "gauss_seidel_edo.h"

real_t pp (real_t x);
real_t qq (real_t x);
real_t rr (real_t x);

int main () {

  EDo edo = {5, 0, 1, -1, 0, pp, qq, rr};

  real_t *Y = calloc(edo.n, sizeof(real_t));

  Tridiag *tridiag = genTridiag(&edo);
  gaussSeidel_3Diag(tridiag, Y, MAXIT);
  prnEDOsl(&edo, 0);
  prnVetor(Y, edo.n);

  for (int i = 0; i < edo.n; i++)
    Y[i] = 0;

  gaussSeidel_EDO(&edo, Y, MAXIT);
  prnVetor(Y, edo.n);

  // aplica gauss-seidel para malhas 5, 10, 100 e 1000
  // Mostra resultados

  free(Y);

  return 0;
}

real_t pp (real_t x) {
  return x+1;
}

real_t qq (real_t x) {
  return -2*x;
}

real_t rr (real_t x) {
  return (1+x)*(1-x)*exp(-x);
}


