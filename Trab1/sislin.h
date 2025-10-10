#ifndef __SISLIN_H__
#define __SISLIN_H__

#include "utils.h"


void criaKDiagonal(int n, int k, real_t **A, real_t *B);

void genSimetricaPositiva(real_t **A, real_t *b, int n, int k, real_t **ASP, real_t *bsp, rtime_t *tempo);

void geraDLU(real_t **A, int n, int k, real_t **D, real_t **L, real_t **U, rtime_t *tempo);

void geraPreCond(real_t **D, real_t **L, real_t **U, real_t w, int n, int k, real_t **M, rtime_t *tempo);

real_t calcResiduoSL(real_t **A, real_t *b, real_t *X, int n, int k, rtime_t *tempo);

void ssor_Minv(real_t **L, real_t **U,real_t **D, int n, int k, real_t w, rtime_t *tempo, real_t **M_inv);

#endif // __SISLIN_H__
