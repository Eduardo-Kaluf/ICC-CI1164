#ifndef __ELIMINACAO_GAUSS__
#define __ELIMINACAO_GAUSS__

void lower_triangularization(linear_system_t *C);

void backward_substitution(linear_system_t *C, real_t *X);

#endif
