#ifndef __GAUSS_SEIDEL_EDO_H__
#define __GAUSS_SEIDEL_EDO_H__

#include "edo.h"

rtime_t gaussSeidel_3Diag (Tridiag *sl, real_t *Y, unsigned int maxiter);

#endif // __GAUSS_SEIDEL_EDO_H__