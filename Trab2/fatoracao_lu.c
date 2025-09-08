// EDUARDO KALUF - GRR 20241770

#include "fatoracao_lu.h"

#include <stdlib.h>

#include "edo.h"
#include "utils.h"


void fatoracaoLU(int n, double A[][n]) {
    for (int i = 0; i < n; ++i) {
        for (int k = i + 1; k < n; ++k) {
            double m = A[k][i] / A[i][i]; // INFERIOR DIVIDIA PELA PRINCIPAL
            A[k][i] = m; // DIAGONAL INFERIOR
            for (int j = i+1; j < n; ++j)
                A[k][j] -= A[i][j] * m; // PRINCIPAL - SUPERIOR
        }
    }
}

void fatoracaoLuTridiag(Tridiag *tridiag, int n) {
    for (int i = 0; i < n; ++i) {
        double m = tridiag->Di[i + 1] / tridiag->D[i]; // INFERIOR DIVIDIA PELA PRINCIPAL
        tridiag->Di[i] = m; // DIAGONAL INFERIOR
        tridiag->D[i + 1] -= tridiag->Ds[i] * m;
    }
}

void resolveSlTridiag(Tridiag *tridiag, double *X) {
    double *Y = malloc(tridiag->n * sizeof(double));

    // resolve o sistema LY = B
    for (int i = 0; i < tridiag->n; ++i) {
        Y[i] = tridiag->B[i];

        if (i > 0)
            Y[i] -= tridiag->Di[i - 1] * Y[i - 1];
    }

    // resolve o sistema UX = Y
    for (int i = tridiag->n - 1; i >= 0; --i) {
        X[i] = Y[i];
        if (i + 1 < tridiag->n)
            X[i] -= tridiag->Ds[i] * X[i + 1];
        X[i] /= tridiag->D[i];
    }

    free(Y);
}

void resolveSL(int n, double LU[][n], double *B, double *X) {
    double *Y = malloc(n * sizeof(double));

    // resolve o sistema LY = B
    for (int i = 0; i < n; ++i) {
         Y[i] = B[i];
         for (int j = 0; j < i; ++j)
             Y[i] -= LU[i][j]*Y[j];
    }

    // resolve o sistema UX = Y
    for (int i = n-1; i >= 0; --i) {
         X[i] = Y[i];
         for (int j = i+1; j < n; ++j)
             X[i] -= LU[i][j] * X[j];
         X[i] /= LU[i][i];
    }

    free(Y);
}