#ifndef GRADIENTE_CONJUGADO_H
#define GRADIENTE_CONJUGADO_H
#include "utils.h"

real_t calc_gradiente_conjugado(real_t **A, real_t *B, real_t *X, real_t **M, int n, int maxit, real_t epsilon, rtime_t *tempo);

real_t calc_norm(real_t *X, real_t *X_old, int n);

#endif
