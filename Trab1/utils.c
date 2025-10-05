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
    scanf("%f", w);
    scanf("%d", maxit);
    scanf("%f", epsilon);
}

void fill_zeros_matrix(real_t **m, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m[i][j] = 0.0;
}

void fill_zeros_vector(real_t *v, int n) {
    memset(v, 0, n * sizeof(real_t));
}

void generate_identity(real_t **m, int n) {
    fill_zeros_matrix(m, n);

    for (int i = 0; i < n; i++)
        m[i][i] = 1.0;
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
