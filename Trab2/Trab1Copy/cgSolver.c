#include <stdlib.h>
#include <stdio.h>

#include "gradiente_conjugado.h"
#include "matriz.h"
#include "sislin.h"
#include "utils.h"
#include "vetor.h"


int main() {
    srandom(20252);

    #ifdef _LIK_
        LIKWID_MARKER_INIT;
    #endif

    rtime_t total_time = timestamp();

    printf("Trab1 - Standard \n");

    int n;
    real_t *X, *B, *BSP, **A, **ASP, **M, **D, **L, **U;
    rtime_t time_pc, time_simetrica, time_iter, time_residuo, time_dlu = 0.0;

    scanf("%d", &n);
    int k = K;
    int maxit = MAX_IT;
    real_t w = W;

    if (k > n)
        handle_error("K não pode ser maior do que n");

    alloc_vectors(&X, &B, &BSP, n);
    alloc_matrixes(&A, &ASP, &M, &D, &L, &U, n);

    // ----------------------------------------- //

    criaKDiagonal(n, k, A, B);

    #ifdef _DEBUG_
        print_matrix(A, B, n);
        print_vector(B, n);
        printf("\n");
    #endif

    genSimetricaPositiva(A, B, n, k, ASP, BSP, &time_simetrica);

    if (w >= 0.0)
        geraDLU(ASP, n, k, D, L, U, &time_dlu);

    geraPreCond(D, L, U, w, n, k, M, &time_pc);

    real_t norm = calc_gradiente_conjugado(ASP, BSP, X, M, n, maxit, &time_iter);

    #ifdef _LIK_
        LIKWID_MARKER_START(markerName("RESIDUO", 1));
    #endif

    real_t residuo = calcResiduoSL(A, B, X, n, k, &time_residuo);

    #ifdef _LIK_
        LIKWID_MARKER_STOP(markerName("RESIDUO", 1));
    #endif

    rtime_t total_pc_time = time_pc + time_simetrica + time_dlu;

    print_results(n, X, norm, residuo, total_pc_time, time_iter, time_residuo);

    free_all_memory(&X, &B, &BSP, &A, &ASP, &M, &D, &L, &U, n);

    printf("\nTotal Time %f\n", timestamp() - total_time);

    #ifdef _LIK_
        LIKWID_MARKER_CLOSE;
    #endif

    return 0;
}
