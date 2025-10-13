#include "matriz.h"

// Fator de unroll
#define UF 4

void multMatVetOtimizada(MatRow mat, Vetor v, int m, int n, Vetor res);
    
void multMatMatOtimizada(MatRow A, MatRow B, int n, MatRow C);
