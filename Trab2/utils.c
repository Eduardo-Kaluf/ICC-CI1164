#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "utils.h"
#include "vetor.h"


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

void alloc_vectors(real_t **X, real_t **M, int n) {
    *X   = alloc_single_vector(USE_CALLOC, sizeof(real_t), n);
    *M   = alloc_single_vector(USE_CALLOC, sizeof(real_t), n);
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

void handle_error(char *message) {
    fprintf(stderr, "FATAL ERROR: %s\n", message);

    exit(EXIT_FAILURE);
}
