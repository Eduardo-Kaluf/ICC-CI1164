#include <stdlib.h>
#include <stdio.h>

#include "gradiente_conjugado.h"
#include "csr_matriz.h"
#include "sislin.h"
#include "utils.h"

#ifdef _LIK_
	#include <likwid.h>
#endif


int main() {
    srandom(20252);

    #ifdef _LIK_
        LIKWID_MARKER_INIT;
    #endif

    rtime_t total_time = timestamp();

    printf("Trab2 - Optimazed \n");

    int n;

    scanf("%d", &n);

    if (K > n)
        handle_error("K não pode ser maior do que n");

    const int nnz_capacity = K * n - OFF_SET;

    real_t *X, *M;
    rtime_t time_pc, time_simetrica, time_iter, time_residuo = 0.0;

    alloc_vectors(&X, &M, n);

    csr *C = alloc_csr(n, nnz_capacity);

    // ----------------------------------------- //

    criaKDiagonal(C);

    #ifdef _DEBUG_
        print_csr(C, STANDARD_MODE);
    #endif

    csr *C_SP = genSimetricaPositiva(C, &time_simetrica);

    geraCondicionadorJacobi(C_SP, M, &time_pc);

    const real_t norm = calc_gradiente_conjugado(C_SP, X, M, &time_iter);

    #ifdef _LIK_
        LIKWID_MARKER_START(markerName("RESIDUO", 1));
    #endif

    const real_t residuo = calcResiduoSL(C_SP, X, &time_residuo);

    #ifdef _LIK_
        LIKWID_MARKER_STOP(markerName("RESIDUO", 1));
    #endif

    print_results(n, X, norm, residuo, time_pc + time_simetrica, time_iter, time_residuo);

    free(X); free(M); free_csr(C_SP); free_csr(C);

    printf("\nTotal Time %f\n",  timestamp() - total_time);

    #ifdef _LIK_
        LIKWID_MARKER_CLOSE;
    #endif

    return 0;
}
