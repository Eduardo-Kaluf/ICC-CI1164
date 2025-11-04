#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <fenv.h>
#include <math.h>
#include <stdint.h>

#include <likwid.h>

#include "utils.h"

#define UNROLL_FACTOR 4

/////////////////////////////////////////////////////////////////////////////////////
//   AJUSTE DE CURVAS
/////////////////////////////////////////////////////////////////////////////////////

void montaSL(double **A, double *b, int n, long long int p, double *x, double *y) {
  for (int i = 0; i < n; i += 1)
    for (int j = 0; j < n; j += UNROLL_FACTOR) {
      A[i][j] = 0.0;
      
      int factor = i + j;

      for (long long int k = 0; k < p; k += 1) {
        double manual_pow1 = 1; 
        double manual_pow2 = 1; 
        double manual_pow3 = 1; 
        double manual_pow4 = 1; 

        for (int counter = 0; counter < factor; counter++) {
          manual_pow1 *= x[k]; 
          manual_pow2 *= x[k]; 
          manual_pow3 *= x[k]; 
          manual_pow4 *= x[k]; 
        }

        manual_pow2 *= x[k];

        manual_pow3 *= x[k] * x[k]; 
        
        manual_pow4 *= x[k] * x[k] * x[k];

        A[i][j]     += manual_pow1;
        A[i][j + 1] += manual_pow2;
        A[i][j + 2] += manual_pow3;
        A[i][j + 3] += manual_pow4;
      }
    }

  for (int i = 0; i < n; i += UNROLL_FACTOR) {
    b[i] = 0.0;
    
    for (long long int k = 0; k < p; ++k) {
      double manual_pow1 = 1; 
      double manual_pow2 = 1; 
      double manual_pow3 = 1; 
      double manual_pow4 = 1; 

      for (int counter = 0; counter < i; counter++) {
        manual_pow1 *= x[k]; 
        manual_pow2 *= x[k]; 
        manual_pow3 *= x[k]; 
        manual_pow4 *= x[k]; 
      }

      manual_pow2 *= x[k];

      manual_pow3 *= x[k] * x[k]; 
      
      manual_pow4 *= x[k] * x[k] * x[k];

      b[i] += manual_pow1 * y[k];
      b[i + 1] += manual_pow2 * y[k];
      b[i + 2] += manual_pow3 * y[k];
      b[i + 3] += manual_pow4 * y[k];
    }
  }
}

// TODO TODO TODO OPTIMAZE THIS ONE
void eliminacaoGauss(double **A, double *b, int n) {
  for (int i = 0; i < n; ++i) {
    int iMax = i;

    for (int k = i+1; k < n; ++k)
      if (A[k][i] > A[iMax][i])
        iMax = k;

    if (iMax != i) {
      double *tmp, aux;
      tmp = A[i];
      A[i] = A[iMax];
      A[iMax] = tmp;

      aux = b[i];
      b[i] = b[iMax];
      b[iMax] = aux;
    }

    for (int k = i+1; k < n; ++k) {
      double m = A[k][i] / A[i][i];

      A[k][i]  = 0.0;

      for (int j = i+1; j < n; ++j)
        A[k][j] -= A[i][j]*m;
      
      b[k] -= b[i]*m;
    }
  }
}


void retrossubs(double **A, double *b, double *x, int n) {
  for (int i = n-1; i >= 0; --i) {
    double sum = b[i];

    int limit = n - (UNROLL_FACTOR - 1);

    int j;
    for (j = i + 1; j < limit; j += UNROLL_FACTOR) {
      sum -= A[i][j + 0]*x[j + 0];
      sum -= A[i][j + 1]*x[j + 1];
      sum -= A[i][j + 2]*x[j + 2];
      sum -= A[i][j + 3]*x[j + 3];
    }

    for (; j < n; j++)
      sum -= A[i][j]*x[j];

    x[i] = sum / A[i][i];
  }
}


double Pol(double x, int G, double *alpha) {
  double Px = alpha[0];
  for (int i = 1; i <= G; ++i)
    Px += alpha[i]*pow(x,i);
  
  return Px;
}

int main() {

  int G, g; // G -> grau do polinomio
  long long int P, p; // P -> no. de pontos
  string_t marker;

  scanf("%d %lld", &G, &P);
  p = P;   // quantidade de pontos
  g = G+1; // tamanho do SL (G + 1)

  double *x = (double *) malloc(sizeof(double)*p);
  double *y = (double *) malloc(sizeof(double)*p);

  // ler numeros
  for (long long int i = 0; i < p; ++i)
    scanf("%lf %lf", x+i, y+i);

  double **A = (double **) malloc(sizeof(double *)*g);
  for (int i = 0; i < g; ++i)
    A[i] = (double *) malloc(sizeof(double)*g);
  
  double *b = (double *) malloc(sizeof(double)*g);
  double *alpha = (double *) malloc(sizeof(double)*g); // coeficientes ajuste

  LIKWID_MARKER_INIT;
  
  // (A) Gera SL
  marker = markerName("SL",p);
  LIKWID_MARKER_START (marker);
  double tSL = timestamp();
  montaSL(A, b, g, p, x, y);
  tSL = timestamp() - tSL;
  LIKWID_MARKER_STOP(marker);
  free(marker);

  // (B) Resolve SL
  marker = markerName("EG",p);
  LIKWID_MARKER_START(marker);
  double tEG = timestamp();
  eliminacaoGauss(A, b, g); 
  retrossubs(A, b, alpha, g); 
  tEG = timestamp() - tEG;
  LIKWID_MARKER_STOP(marker);
  free(marker);

  LIKWID_MARKER_CLOSE;

  // Imprime coeficientes
  for (int i = 0; i < g; ++i)
    printf("%1.15e ", alpha[i]);
  puts("");

  // Imprime resíduos
  for (long long int i = 0; i < p; ++i)
    printf("%1.15e ", fabs(y[i] - Pol(x[i],G,alpha)) );
  puts("");

  // Imprime os tempos
  printf("%lld %1.10e %1.10e\n", P, tSL, tEG);

  return 0;
}
