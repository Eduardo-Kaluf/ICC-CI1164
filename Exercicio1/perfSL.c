//#include <likwid.h>

#include <stdio.h>

#include "utils.h"
#include "sislin.h"
#include "eliminacao_gauss.h"
#include "gauss_seidel.h"

void print_formated(char *name, rtime_t time, real_t *X, linear_system_t *input) {
    real_t *R = malloc(input->n * sizeof(real_t));
    residuo(input, X, R, input->n);

    printf("%s: \n%f ms\n", name, time);

    prnVetor(X, input->n);

    prnVetor(R, input->n);

    printf("\n");

    free(R);
}


int main() {
    linear_system_t *EG_system = lerSisLin();
    real_t *EG_X = malloc(EG_system->n * sizeof(real_t));

    linear_system_t *GS_system = dupSisLin(EG_system);
    real_t *GS_X = malloc(GS_system->n * sizeof(real_t));

    // EG VERIFICATION

    rtime_t time_EG = timestamp();
    lower_triangularization(EG_system);
    backward_substitution(EG_system, EG_X);
    print_formated("EG", timestamp() - time_EG, EG_X, EG_system);

    // GS VERIFICATION

    real_t norm;
    rtime_t time_GS = timestamp();

    gauss_seidel(GS_system, GS_X, TOL, MAX_ITERATIONS , &norm);
    print_formated("GS", timestamp() - time_GS, GS_X, GS_system);

    liberaSisLin(EG_system);
    free(EG_X);
    liberaSisLin(GS_system);
    free(GS_X);

    printf("TESTE ENDED\n\n");

    return 0;
}
