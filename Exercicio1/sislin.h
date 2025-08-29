#ifndef __SISLIN_H__
#define __SISLIN_H__

// Parâmetros default para teste de convergência
#define MAX_ITERATIONS 50
#define TOL  1.0e-4

// Estrutura para definiçao de um sistema linear qualquer
typedef struct {
    int n; // tamanho do SL
    real_t **A; // coeficientes
    real_t *b; // termos independentes
} linear_system_t;

// Alocaçao e desalocação de matrizes
linear_system_t* alocaSisLin (int n);
void liberaSisLin (linear_system_t *SL);

// Leitura e impressão de sistemas lineares
linear_system_t *lerSisLin ();
linear_system_t *dupSisLin (linear_system_t *src);
void prnSisLin (linear_system_t *SL);
void prnVetor (real_t *vet, int n);

// Funções auxiliares
real_t normMax(real_t *X1, real_t *X0, int n);
real_t normL2(real_t *X, int n);
void residuo(linear_system_t *SL, real_t *X, real_t *R, int n);

#endif // __SISLIN_H__

