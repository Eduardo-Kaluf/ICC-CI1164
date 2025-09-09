#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "utils.h"
#include "gauss_seidel.h"
#include "edo.h"

rtime_t gaussSeidel_3Diag(Tridiag *sl, real_t *Y, unsigned int maxiter) {
    int n = sl->n;
    rtime_t tTotal = timestamp();

    for (int k = 0; k < maxiter; k++) {
        Y[0] = (sl->B[0] - sl->Ds[0] * Y[1]) / sl->D[0];

        for (int i = 1; i < n - 1; ++i)
            Y[i] = (sl->B[i] - sl->Di[i - 1] * Y[i - 1] - sl->Ds[i] * Y[i + 1]) / sl->D[i];

        Y[n - 1] = (sl->B[n - 1] - sl->Di[n - 2] * Y[n - 2] ) / sl->D[n - 1];
    }

    return timestamp() - tTotal;
}
