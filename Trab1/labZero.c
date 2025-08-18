#include <fenv.h>
#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

// TODO TODO TODO DOES THIS NEED TO BE ON?
//#pragma STDC FENV_ACCESS ON

int main () {
    fesetround(FE_DOWNWARD);

    const enum CriteriosDeParada tests[TESTS_QUANTITY] = {RELATIVE_ERROR_TEST, EPSILON_TEST, ULP_TEST};
    const enum CalcType calcTypes[CALC_QUANTITY] = {FAST, SLOW};

    Polinomio pol;
    real_t a, b;

    // Reads the polynomial data
    scanf("%d", &pol.grau);

    pol.p = malloc((pol.grau + 1) * sizeof(real_t));

    for (int i=pol.grau; i >=0; --i)
        scanf("%lf", &pol.p[i]);

    // Reads the interval
    scanf("%lf %lf", &a, &b);

    int it;
    real_t raiz, error, time;
    for (int i = 0; i < CALC_QUANTITY; i++) {

        if (calcTypes[i] == FAST)
            printf("RAPIDO\n\n");
        else
            printf("\nLENTO\n\n");

        for (int j = 0; j < TESTS_QUANTITY; j++) {
            it = 0;

            time = timestamp();
            error = bisseccao(pol, a, b, tests[j], &it, &raiz, calcTypes[i]);
            time = timestamp() - time;

            printf("%-7s %+.15e %+.15e %3d %.8e\n", "bissec", raiz, error, it, time);
        }

        for (int j = 0; j < TESTS_QUANTITY; j++) {
            it = 0;

            time = timestamp();
            error = newtonRaphson(pol, (a + b) / 2, tests[j], &it, &raiz, calcTypes[i]);
            time = timestamp() - time;

            printf("%-7s %+.15e %+.15e %3d %.8e\n", "newton", raiz, error, it, time);
        }
    }

    return 0;
}
