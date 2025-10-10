#include <stdlib.h>

#include "gradiente_conjugado.h"
#include "sislin.h"
#include "utils.h"


int main() {
    srandom(20252);

    int n, k, maxit;
    real_t w, epsilon;
    real_t *X, *B, *BSP, **A, **ASP, **M, **D, **L, **U;
    rtime_t time_pc, time_simetrica, time_iter, time_residuo, time_dlu = 0.0;

    read_input(&n, &k, &w, &maxit, &epsilon);

    alloc_vectors(&X, &B, &BSP, n);
    alloc_matrixes(&A, &ASP, &M, &D, &L, &U, n);

    // ----------------------------------------- //

    criaKDiagonal(n, k, A, B);

    genSimetricaPositiva(A, B, n, k, ASP, BSP, &time_simetrica);

    if (w >= 0.0)
        geraDLU(ASP, n, k, D, L, U, &time_dlu);

    geraPreCond(D, L, U, w, n, k, M, &time_pc);

    real_t norm = calc_gradiente_conjugado(ASP, BSP, X, M, n, maxit, epsilon, &time_iter);

    real_t residuo = calcResiduoSL(ASP, BSP, X, n, k, &time_residuo);

    rtime_t total_pc_time = time_pc + time_simetrica + time_dlu;

    print_results(n, X, norm, residuo, total_pc_time, time_iter, time_residuo);

    free_all_memory(&X, &B, &BSP, &A, &ASP, &M, &D, &L, &U, n);

    return 0;
}
