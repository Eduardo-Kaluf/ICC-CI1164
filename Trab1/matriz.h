#ifndef __MATRIZ_H__
#define __MATRIZ_H__

#include "utils.h"

void alloc_single_matrix(real_t ***m, int n);

void free_matrix(real_t **m, int n);

void fill_zeros_matrix(real_t **m, int n);

void copy_matrix(real_t **A, real_t **B, int n);

void print_matrix(real_t **m, int n);

void sum_matrix (real_t **A, real_t **B, int n, real_t **C);

void matrix_times_scalar(real_t **A, int n, real_t value, real_t **dest);

void matrix_times_vector(real_t **m, int n, real_t *v, real_t *rv);

void matrix_times_matrix(real_t **A, real_t **B, int n, real_t **C);

#endif // __MATRIZ_H__
