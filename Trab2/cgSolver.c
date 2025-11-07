#include <stdlib.h>
#include <stdio.h>

#include "gradiente_conjugado.h"
#include "csr_matriz.h"
#include "sislin.h"
#include "utils.h"


int main() {
    srandom(20252);

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

    csr *C_SP = genSimetricaPositiva(C, &time_simetrica);

    #ifdef _DEBUG_
        print_csr(C, STANDARD_MODE);
        printf("\n\n");
        print_csr(C_SP, STANDARD_MODE);
    #endif

    geraCondicionadorJacobi(C_SP, M, &time_pc);

    const real_t norm = calc_gradiente_conjugado(C_SP, X, M, &time_iter);

    const real_t residuo = calcResiduoSL(C_SP, X, &time_residuo);

    print_results(n, X, norm, residuo, time_pc + time_simetrica, time_iter, time_residuo);

    free(X); free(M);

    return 0;
}
