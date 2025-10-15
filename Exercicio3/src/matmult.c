#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include <likwid.h>

#include "matriz.h"
#include "matriz_otimizada.h"
#include "utils.h"

/**
 * Exibe mensagem de erro indicando forma de uso do programa e termina
 * o programa.
 */

static void usage(char *progname) {
    fprintf(stderr, "Forma de uso: %s [ <ordem> ] \n", progname);
    exit(1);
}



/**
 * Programa principal
 * Forma de uso: matmult [ -n <ordem> ]
 * -n <ordem>: ordem da matriz quadrada e dos vetores
 *
 */

int main(int argc, char *argv[]) {
    
    LIKWID_MARKER_INIT;

    int n=DEF_SIZE;
    
    MatRow mRow_1, mRow_2, resMat;
    Vetor vet, res;
    
    /* =============== TRATAMENTO DE LINHA DE COMANDO =============== */

    if (argc < 2)
        usage(argv[0]);

    n = atoi(argv[1]);
    
    /* ================ FIM DO TRATAMENTO DE LINHA DE COMANDO ========= */
    
    srandom(20232);
        
    res = geraVetor (n, 0); // (real_t *) malloc (n*sizeof(real_t));
    resMat = geraMatRow(n, n, 1);
        
    mRow_1 = geraMatRow (n, n, 0);
    mRow_2 = geraMatRow (n, n, 0);

    vet = geraVetor (n, 0);

    if (!res || !resMat || !mRow_1 || !mRow_2 || !vet) {
        fprintf(stderr, "Falha em alocação de memória !!\n");
        liberaVetor ((void*) mRow_1);
        liberaVetor ((void*) mRow_2);
        liberaVetor ((void*) resMat);
        liberaVetor ((void*) vet);
        liberaVetor ((void*) res);
        exit(2);
    }
        
    #ifdef _DEBUG_
        prnMat (mRow_1, n, n);
        prnMat (mRow_2, n, n);
        prnVetor (vet, n);
        printf ("=================================\n\n");
    #endif /* _DEBUG_ */

    rtime_t t_mat_vet = timestamp();

    LIKWID_MARKER_START("multMatVet");

    multMatVet (mRow_1, vet, n, n, res);
    
    LIKWID_MARKER_STOP("multMatVet");

    t_mat_vet = timestamp() - t_mat_vet;

    
    rtime_t t_mat_vet_otimizado = timestamp();

    LIKWID_MARKER_START("multMatVetOtimizada");
    
    multMatVetOtimizada(mRow_1, vet, n, n, res);
    
    LIKWID_MARKER_STOP("multMatVetOtimizada");

    t_mat_vet_otimizado = timestamp() - t_mat_vet_otimizado;

    rtime_t t_mat_mat = timestamp();

    LIKWID_MARKER_START("multMatMat");
    
    multMatMat (mRow_1, mRow_2, n, resMat);
    
    LIKWID_MARKER_STOP("multMatMat");
    
    t_mat_mat = timestamp() - t_mat_mat;
    
    rtime_t t_mat_mat_otimizado = timestamp();

    LIKWID_MARKER_START("multMatMatOtimizada");
    
    multMatMatOtimizada(mRow_1, mRow_2, n, resMat);
    
    LIKWID_MARKER_STOP("multMatMatOtimizada");

    t_mat_mat_otimizado = timestamp() - t_mat_mat_otimizado;
    
    #ifdef _DEBUG_
        prnVetor (res, n);
        prnMat (resMat, n, n);
    #endif /* _DEBUG_ */

    printf("%d, %.8g, %.8g, %.8g, %.8g\n", n, t_mat_vet, t_mat_vet_otimizado, t_mat_mat, t_mat_mat_otimizado);

    liberaVetor ((void*) mRow_1);
    liberaVetor ((void*) mRow_2);
    liberaVetor ((void*) resMat);
    liberaVetor ((void*) vet);
    liberaVetor ((void*) res);
	
    LIKWID_MARKER_CLOSE;
    
    return 0;
}

