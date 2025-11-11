#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"


#define DIFF 0.0

#define NRAND    ((real_t) random() / RAND_MAX)  // drand48() 
#define SRAND(a) srandom(a) // srand48(a)


real_t styblinskiTang(real_t *vars, int n_dimensions) {

  real_t sum = 0.0;

  for (int i = 0; i < n_dimensions; i++) {
    real_t xi = vars[i];
    sum += pow(xi, 4) - 16 * xi * xi + 5 * xi;
  }

  return sum / 2;
}

// Integral Monte Carlo da função Styblinski-Tang de 2 variáveis
real_t monteCarlo(real_t a, real_t b, int namostras, int dimensions) {
  real_t resultado;
  real_t soma = 0.0;
  
  printf("Metodo de Monte Carlo (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), variaveis = 2\n", a, b, namostras);
  
  rtime_t t_inicial = timestamp();
  
  /*
    
    AQUI IMPLEMENTE O CÁLCULO DA INTEGRAL  PELO
    MÉTODO DE MONTE CARLO
    
  */
  
  rtime_t t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);
  
  return resultado;
}


real_t retangulos_xy(real_t a, real_t b, int npontos) {

  real_t h = (b - a) / npontos;
  real_t soma = 0.0;
  
  printf("Metodo dos Retangulos (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), h = (%lg)\n", a, b, npontos, h);
  
  rtime_t t_inicial = timestamp();

  real_t vars[2];
  real_t area_elemento = h * h;

  for (int j = 0; j < npontos; j++) {
    vars[1] = a + j * h;

    for (int i = 0; i < npontos; i++) {
      vars[0] = a + i * h;
      
      soma += styblinskiTang(vars, 2) * area_elemento;
    }
  }

  rtime_t t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);
  
  return soma;
}


int main(int argc, char **argv) {

  if (argc < 5) {
    printf("Utilização: %s inicial final n_amostras n_variaveis\n", argv[0]);
    return 1;
  }

  SRAND(20252);
  
  real_t resultRet = retangulos_xy(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
  printf("%f\n", resultRet);

  real_t resultMonte = monteCarlo(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
  printf("%f\n", resultMonte);

  return 0;
}

