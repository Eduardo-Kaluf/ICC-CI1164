#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdnoreturn.h>

#include "utils.h"
#include "matriz.h"
#include "vetor.h"


int max (int a, int b) {
    return (a > b) ? a : b;
}

int min (int a, int b) {
    return (a < b) ? a : b;
}

rtime_t timestamp(void) {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
    return ( (rtime_t) tp.tv_sec*1.0e3 + (rtime_t) tp.tv_nsec*1.0e-6 );
}

string_t markerName(string_t baseName, int n) {
    string_t mark = (string_t) malloc( (strlen(baseName)+1) + numDigits(n) + 1 );

    sprintf(mark, "%s_%u", baseName,n);

    return mark;
}

void read_input(int *n, int *k, real_t *w, int *maxit, real_t *epsilon) {
    if (scanf("%d %d %lf %d %lf", n, k, w, maxit, epsilon) != N_INPUTS)
        handle_error("Erro ao ler o input");
}

void alloc_vectors(real_t **X, real_t **B, real_t **BSP, int n) {
    *X   = alloc_single_vector(USE_CALLOC, sizeof(real_t), n);
    *B   = alloc_single_vector(USE_MALLOC, sizeof(real_t), n);
    *BSP = alloc_single_vector(USE_CALLOC, sizeof(real_t), n);
}

void alloc_matrixes(real_t ***A, real_t ***ASP, real_t ***M, real_t ***D, real_t ***L, real_t ***U, int n) {
    alloc_single_matrix(A, n);
    alloc_single_matrix(ASP, n);
    alloc_single_matrix(M, n);
    alloc_single_matrix(D, n);
    alloc_single_matrix(L, n);
    alloc_single_matrix(U, n);
}

void print_results(int n, real_t *X, real_t norm, real_t residuo, rtime_t time_pc, rtime_t time_iter, rtime_t time_residuo) {
    if (!X)
        handle_error("Tentativa de acesso a um ponteiro nulo");

    printf("%d\n", n);

    print_vector(X, n);

    printf("%.8g\n"
                 "%.16g\n"
                 "%.8g\n"
                 "%.8g\n"
                 "%.8g\n", norm, residuo, time_pc, time_iter, time_residuo);

}

void free_all_memory(real_t **X, real_t **B, real_t **BSP, real_t ***A, real_t ***ASP, real_t ***M, real_t ***D, real_t ***L, real_t ***U, int n) {
    if (*X) {
        free(*X);
        *X = NULL;
    }

    if (*B) {
        free(*B);
        *B = NULL;
    }

    if (*BSP) {
        free(*BSP);
        *BSP = NULL;
    }

    free_matrix(A, n); free_matrix(ASP, n); free_matrix(M, n); free_matrix(D, n); free_matrix(L, n); free_matrix(U, n);
}

void handle_error(char *message) {
    fprintf(stderr, "FATAL ERROR: %s\n", message);

    exit(EXIT_FAILURE);
}
