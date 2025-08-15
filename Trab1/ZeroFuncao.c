#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

bool getCriterioDeParada(enum CriterioDeParada criterioParada, real_t x_old, real_t x_new, real_t fx, real_t *error) {
    switch (criterioParada) {
        case RELATIVE_ERROR_TEST:
            *error = fabs((x_new - x_old) / x_new);
            return *error <= EPS; // TODO TODO TODO VERIFICAR MENOR IGUAL DA MANEIRA CORRETA QUE FOI APRESENTADA EM SALA
        case EPSILON_TEST:
            *error = fabs(fx);
            return *error <= DBL_EPSILON;
        default:
            long long int x_old_ulp = 0, x_new_ulp = 0;

            for (int i=63; i>=0; i--) {
                long long int mask = 1LL << i;

                if (x_old_ulp & mask)
                    x_old_ulp += mask;
                if (x_new_ulp & mask)
                    x_new_ulp += mask;
            }

            *error = (double) llabs(x_old_ulp - x_new_ulp) - 1;
            return *error <= ULPS;
    }
}

real_t newtonRaphson(Polinomio p, real_t x0, enum CriteriosDeParada criterioParada, int *it, real_t *raiz) {
    real_t error, x_new = x0, x_old, px, dpx;

    do {
        x_old = x_new;

        calcPolinomio_rapido(p, x_old, &px, &dpx);

        x_new = x_old - (px / dpx);

        calcPolinomio_rapido(p, x_new, &px, &dpx);

        (*it)++;
    } while (getCriterioDeParada(criterioParada, x_old, x_new, px, &error) && *it < MAXIT);

    *raiz = x_new;
    return error;
}

real_t bisseccao(Polinomio p, real_t a, real_t b, enum CriteriosDeParada criterioParada, int *it, real_t *raiz) {
    real_t px1, dpx1, px2, dpx2, xm_old, xm_new = a, val, error = 0;

    do {
        xm_old = xm_new;
        xm_new = (a + b) / 2;
        calcPolinomio_rapido(p, a, &px1, &dpx1);
        calcPolinomio_rapido(p, xm_new, &px2, &dpx2);

        val = px1 * px2;

        if (val < 0)
            b = xm_new;
        else if (val > 0)
            a = xm_new;

        (*it)++;
    } while (getCriterioDeParada(criterioParada, xm_old, xm_new, px2, &error) && *it < MAXIT && val != 0);

    *raiz = xm_new;
    return error;
}

void calcPolinomio_rapido(Polinomio p, real_t x, real_t *px, real_t *dpx) {
    real_t b = 0;
    real_t c = 0;

    for (int i = p.grau; i > 0; --i) {
        b = b*x + p.p[i];
        c = c*x + b;
    }

    b = b*x + p.p[0];
    *px = b;
    *dpx = c;
}

void calcPolinomio_lento(Polinomio p, real_t x, real_t *px, real_t *dpx) {
    for (int i = p.grau; i >= 0; i --)
        *px += p.p[i] * pow(x, i);
 
    for (int i = p.grau; i >= 1; i --)
        *dpx += p.p[i] * i * pow(x, i - 1);
}
