#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utils.h"


rtime_t timestamp (void) {
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
    scanf("%d", n);
    scanf("%d", k);
    scanf("%lf", w);
    scanf("%d", maxit);
    scanf("%lf", epsilon);
}

void fill_zeros_matrix(real_t **m, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m[i][j] = 0.0;
}

void fill_zeros_vector(real_t *v, int n) {
    memset(v, 0, n * sizeof(real_t));
}

real_t dot_product(real_t *v1, real_t *v2, int n) {
    real_t sum = 0.0;

    for (int i = 0; i < n; i++)
        sum += v1[i] * v2[i];

    return sum;
}

// rv = m * v
void matrix_times_vector(real_t **m, int n, real_t *v, real_t *rv) {

    fill_zeros_vector(rv, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            rv[i] += m[i][j] * v[j];
}

void print_vector(real_t *v, int n) {
    for (int i = 0; i < n; i++)
        printf("%.16g ", v[i]);

    printf("\n");
}

void print_matrix(real_t **m, int n) {
    for (int i = 0; i < n; i++) {
        printf("[ ");

        for (int j = 0; j < n; j++)
            printf("%.16g ", m[i][j]);

        printf("]\n");
    }

    printf("\n");
}

void alloc_vectors(real_t **X, real_t **B, real_t **BSP, int n) {
    // TODO ADD PROPER ERROR HANDLING

    *X = malloc(n * sizeof(real_t));
    *B = malloc(n * sizeof(real_t));
    *BSP = malloc(n * sizeof(real_t));

    if (!(*X) || !(*B) || !(*BSP))
        fprintf(stderr, "Failed malloc!\n");
}

void alloc_single_matrix(real_t ***m, int n) {
    *m = calloc(n, sizeof(real_t *));
    if (!(*m)) {
        fprintf(stderr, "Failed malloc!\n");
        return;
    }

    for (int i = 0; i < n; ++i) {
        (*m)[i] = calloc(n, sizeof(real_t));

        if (!(*m)[i]) {
            fprintf(stderr, "Failed malloc!\n");

            for (int j = 0; j < i; j++)
                free((*m)[j]);
            free(*m);

            return;
        }
    }
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
    printf("%d\n", n);
    print_vector(X, n);
    printf("%.8g\n%.16g\n%.8g\n%.8g\n%.8g\n", norm, residuo, time_pc, time_iter, time_residuo);
}

void free_matrix(real_t **m, int n) {
    if (m != NULL) {
        for (int i = 0; i < n; i++) {
            if (m[i] != NULL)
                free(m[i]);
        }

        free(m);
    }
}

void free_all_memory(real_t *X, real_t *B, real_t *BSP, real_t **A, real_t **ASP, real_t **M, real_t **D, real_t **L, real_t **U, int n) {
    free(X);
    free(B);
    free(BSP);

    free_matrix(A, n);
    free_matrix(ASP, n);
    free_matrix(M, n);
    free_matrix(D, n);
    free_matrix(L, n);
    free_matrix(U, n);
}
