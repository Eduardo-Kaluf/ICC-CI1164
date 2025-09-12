// EDUARDO KALUF - GRR 20241770

// Foi implementado fatoração LU porém estava errado no enunciado.

#include <stdlib.h>

#include "fatoracao_lu.h"

void fatoracaoLu(Tridiag *tridiag, int n) {
    for (int i = 0; i < n; ++i) {
        real_t m = tridiag->Di[i + 1] / tridiag->D[i];
        tridiag->Di[i] = m;
        tridiag->D[i + 1] -= tridiag->Ds[i] * m;
    }
}

void resolveSl(Tridiag *tridiag, real_t *X) {
    real_t *Y = malloc(tridiag->n * sizeof(real_t));

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
