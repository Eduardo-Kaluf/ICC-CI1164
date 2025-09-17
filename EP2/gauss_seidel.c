// EDUARDO KALUF - GRR 20241770

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "utils.h"
#include "gauss_seidel.h"
#include "edo.h"

int gaussSeidel_3Diag(Tridiag *sl, real_t *Y, int maxiter, real_t *norma) {
    const int n = sl->n;
    int it = 0;

    do {
        // Primeira linha não possui nenhum elemento da diagonal inferior
        Y[0] = (sl->B[0] - sl->Ds[0] * Y[1]) / sl->D[0];

        for (int i = 1; i < n - 1; ++i)
            Y[i] = (sl->B[i] - sl->Di[i - 1] * Y[i - 1] - sl->Ds[i] * Y[i + 1]) / sl->D[i];

        // Última linha não possui nenhum elemento da diagonal superior
        Y[n - 1] = (sl->B[n - 1] - sl->Di[n - 2] * Y[n - 2] ) / sl->D[n - 1];

        *norma = normaL2_3Diag(sl, Y);
        it++;
    } while (*norma > NORMA_STOP && it < maxiter);

    return it;
}

real_t normaL2_3Diag (Tridiag *sl, real_t *Y) {
    const int n = sl->n;

    real_t normaL2 = 0.0;

    for (int i = 0; i < n; i++) {
        real_t Ay_i;

        if (i == 0)
            Ay_i = (sl->D[0] * Y[0]) + (sl->Ds[0] * Y[1]);
        else if (i == n - 1)
            Ay_i = (sl->Di[i-1] * Y[i-1]) + (sl->D[i] * Y[i]);
        else
            Ay_i = (sl->Di[i-1] * Y[i-1]) + (sl->D[i] * Y[i]) + (sl->Ds[i] * Y[i+1]);

        normaL2 += pow(sl->B[i] - Ay_i, 2);
    }

    return sqrt(normaL2);
}