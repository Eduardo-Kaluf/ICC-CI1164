/* Matriz  'normal' (vetor  de  ponteiros (linhas  matriz) para  vetores
   (colunas da matriz), estilo 'Mazieiro/Prog 2'
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "sislin.h"
#include "eliminacaoGauss.h"

static int encontraMax(SistLinear_t *C, int k) {
    real_t max = fabs(C->A[k][k]); 
    int iPivo = k;

    for (int i = k + 1; i < C->n; i++) {
        if ((fabs((C->A)[i][k])) > max) {
            max = (C->A)[i][k];
            iPivo = i;
        }
    }

    return iPivo;
}

static void trocaLinha (SistLinear_t *C, int k, int iPivo) {
    // SWITCH TO MEMORY SWAP INSTEAD OF LOOP
    real_t temp;
    
    for (int i = 0; i < C->n; i++) {
        temp = C->A[k][i];
        C->A[k][i] = C->A[iPivo][i];
        C->A[iPivo][i] = temp;
    }

    temp = C->b[k];
    C->b[k] = C->b[iPivo];
    C->b[iPivo] = temp;
}

/* Seja um S.L. de ordem 'n'
   C = A|B em Ax=B
 */
void triangulariza( SistLinear_t *C ) {
    
    for (int i=0; i < C->n; ++i) {
        unsigned int iPivo = encontraMax(C, i);
        if ( i != iPivo )
            trocaLinha(C, i, iPivo);
        for(int k=i+1; k < C->n; ++k) {
            double m = (C->A)[k][i] / (C->A)[i][i];
            (C->A)[k][i] = 0.0;
            for(int j=i+1; j < C->n; ++j)
                (C->A)[k][j] -= (C->A)[i][j] * m;
            (C->b)[k] -= (C->b)[i] * m;
        }
    }
}

void retrosubst( SistLinear_t *C, real_t *X ) {
    for (int i = (C->n)-1; i >= 0; --i) {
        X[i] = C->b[i];
        for (int j = i+1; j < C->n; ++j)
            X[i] -= C->A[i][j] * X[j];
        X[i] /= C->A[i][i];
    }
}
