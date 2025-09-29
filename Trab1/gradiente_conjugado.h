#ifndef GRADIENTE_CONJUGADO_H
#define GRADIENTE_CONJUGADO_H
#include "utils.h"

void calc_gradiente_conjugado(real_t **A, real_t *B, real_t *X, int n, int k, real_t w, int maxit, double epsilon);

#endif
