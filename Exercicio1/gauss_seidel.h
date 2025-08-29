#ifndef __GAUSS_SEIDEL__
#define __GAUSS_SEIDEL__

#include "sislin.h"

int gauss_seidel(linear_system_t *C, real_t *X, real_t error, int max_iterations, real_t *norm);

#endif
