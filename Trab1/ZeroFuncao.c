#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

#include <stdlib.h>
#include <string.h>


bool getCriterioDeParada(enum CriteriosDeParada criterioParada, real_t x_old, real_t x_new, real_t fx, real_t *error) {
    switch (criterioParada) {
        case RELATIVE_ERROR_TEST:
            double diff = fabs(x_new - x_old);

            if (fabs(x_new) <= ZERO)
                *error = diff;
            else
                *error = diff / fabs(x_new);

            return !(*error <= EPS);
        case EPSILON_TEST:
            *error = fabs(fx);
            return !(*error <= DBL_EPSILON);
        default:
            long long int x_old_bin, x_new_bin;
            memcpy(&x_old_bin, &x_old, sizeof(real_t));
            memcpy(&x_new_bin, &x_new, sizeof(real_t));

            *error = (real_t) llabs(x_old_bin - x_new_bin) - 1;

            if (*error < ZERO)
                *error = 0.0;

            return !(*error <= ULPS);
    }
}

real_t newtonRaphson(Polinomio p, real_t x0, enum CriteriosDeParada criterioParada, int *it, real_t *raiz, enum CalcType calcType) {
    real_t error = 0.0, x_new = x0, x_old, px, dpx;

    do {
        (*it)++;

        x_old = x_new;

        calcPolinomio(p, x_old, &px, &dpx, calcType);

        if (fabs(px) <= ZERO) {
            getCriterioDeParada(criterioParada, x_old, x_new, px, &error);
            break;
        }

        // We could add a second derivative test here, so we less change to fall into a division by zero
        // https://www.researchgate.net/publication/358857049_A_Method_to_Avoid_the_Division-by-Zero_or_Near-Zero_in_Newton-Raphson_Method
        x_new = x_old - (px / dpx);

        calcPolinomio(p, x_new, &px, &dpx, calcType);
    } while (getCriterioDeParada(criterioParada, x_old, x_new, px, &error) && *it < MAXIT);

    *raiz = x_new;
    return error;
}

real_t bisseccao(Polinomio p, real_t a, real_t b, enum CriteriosDeParada criterioParada, int *it, real_t *raiz, enum CalcType calcType) {
    real_t px1, dpx1, px2, dpx2, xm_old, xm_new = a, val, error = 0.0;

    do {
        (*it)++;

        xm_old = xm_new;
        xm_new = (a + b) / 2.0;
        calcPolinomio(p, a, &px1, &dpx1, calcType);
        calcPolinomio(p, xm_new, &px2, &dpx2, calcType);

        val = px1 * px2;

        if (val < ZERO)
            b = xm_new;
        else if (val > ZERO)
            a = xm_new;

    } while (getCriterioDeParada(criterioParada, xm_old, xm_new, px2, &error) && *it < MAXIT);

    *raiz = xm_new;
    return error;
}

void calcPolinomio(Polinomio p, real_t x, real_t *px, real_t *dpx, enum CalcType calcType) {
    if (calcType == FAST) {
        real_t b = 0.0;
        real_t c = 0.0;

        for (int i = p.grau; i > 0; --i) {
            b = b*x + p.p[i];
            c = c*x + b;
        }

        b = b*x + p.p[0];
        *px = b;
        *dpx = c;

        return;
    }

    if (calcType == SLOW) {
        *px = 0.0;
        *dpx = 0.0;

        for (int i = p.grau; i >= 0; i--)
            *px += p.p[i] * pow(x, i);

        for (int i = p.grau; i >= 1; i--)
            *dpx += p.p[i] * i * pow(x, i - 1);
    }
}
