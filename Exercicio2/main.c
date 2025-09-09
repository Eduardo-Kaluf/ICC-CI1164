#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "gauss_seidel_edo.h"

real_t pp (real_t x);
real_t qq (real_t x);
real_t rr (real_t x);

#define MALHA_SIZE 2

int main () {
    real_t *Y;
    Tridiag *tridiag;
    rtime_t tempo;

    // int malha[MALHA_SIZE] = {5};
    int malha[MALHA_SIZE] = {5, 10};
    // int malha[MALHA_SIZE] = {5, 10, 100};
    // int malha[MALHA_SIZE] = {5, 10, 100, 1000};

    EDo edo = {5, 0, 1, -1, 0, pp, qq, rr};

    prnEDOsl(&edo, 0);
    printf("\n");

    for (int i = 0; i < MALHA_SIZE; i++) {
        edo.n = malha[i];
        tridiag = genTridiag(&edo);
        Y = calloc(edo.n, sizeof(real_t));

        // ______________________________ //

        tempo = timestamp();

        gaussSeidel_3Diag(tridiag, Y, MAXIT);

        printf("TRIDIAGONAL\n");
        prnVetor(Y, edo.n);
        printf("NORMA: %.10f\n", normaL2_3Diag(tridiag, Y, (edo.b - edo.a) / (edo.n + 1)));
        printf("TEMPO: %.10f\n\n", timestamp() - tempo);

        zera_array(Y, edo.n);

        // ______________________________ //

        tempo = timestamp();

        gaussSeidel_EDO(&edo, Y, MAXIT);

        printf("EDO\n");
        prnVetor(Y, edo.n);
        printf("NORMA: %.10f\n", normaL2_EDO(&edo, Y));
        printf("TEMPO: %.10f\n\n", timestamp() - tempo);

        zera_array(Y, edo.n);


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


