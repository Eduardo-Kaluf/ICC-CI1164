#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "gauss_seidel_edo.h"

real_t pp (real_t x);
real_t qq (real_t x);
real_t rr (real_t x);

#define MALHA_SIZE 4

int main () {
  real_t *Y;
  Tridiag *tridiag;

  int malha[MALHA_SIZE] = {5, 10, 100, 1000};

  EDo edo = {5, 0, 1, -1, 0, pp, qq, rr};
   prnEDOsl(&edo, 0);

  for (int i = 0; i < 4; i++) {
    edo.n = malha[i];
    tridiag = genTridiag(&edo);
    Y = calloc(edo.n, sizeof(real_t));

    // UNCOMMENT THIS LINE TO SHOW THE SYSTEM

    gaussSeidel_3Diag(tridiag, Y, MAXIT);
    prnVetor(Y, edo.n);
    printf("NORMA: %.10f\n", normaL2_3Diag(tridiag, Y, (edo.b - edo.a) / (edo.n + 1)));

    for (int j = 0; j < edo.n; j++)
      Y[j] = 0;

    gaussSeidel_EDO(&edo, Y, MAXIT);
    prnVetor(Y, edo.n);
    printf("NORMA: %.10f\n", normaL2_EDO(&edo, Y));

    for (int j = 0; j < edo.n; j++)
      Y[j] = 0;

    if (tridiag != NULL) {
      free(tridiag->D);
      free(tridiag->Ds);
      free(tridiag->Di);
      free(tridiag->B);
      free(tridiag);
    }

    if (Y != NULL)
      free(Y);
  }

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


