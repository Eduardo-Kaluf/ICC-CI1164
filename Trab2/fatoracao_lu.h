// EDUARDO KALUF - GRR 20241770

#ifndef FATORACAO_LU_H
#define FATORACAO_LU_H
#include "edo.h"

void fatoracaoLU(int n, double A[][n]);

void fatoracaoLuTridiag(Tridiag *tridiag, int n);

void resolveSL(int n, double LU[][n], double *B, double *X);

void resolveSlTridiag(Tridiag *tridiag, double *X);

#endif //FATORACAO_LU_H
