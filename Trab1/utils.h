#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

// Valor absoluto de um número. Alternativa ao uso da função 'fabs()'
#define ABS(num)  ((num) < 0.0 ? -(num) : (num))

// real_t: tipo usado para representar valores em ponto flutuante
typedef double real_t;

// int_t: tipo usado para representar valores em inteiros
typedef int64_t int_t;

// string_t: tipo usado para representar ponteiros para char/strings
typedef char * string_t;

// rtime_t: tipo usado para representar valores de tempo em ponto flutuante
typedef double rtime_t;

// Número máximo de dígitos em um número
#define numDigits(n)  6  // ( (int) log10(n) + 1 )

// Macro para verificar se valor 'n' é potência de 2 ou não
#define isPot2(n) (n && !(n & (n - 1)))

/**
 * @brief Retorna tempo em milisegundos desde EPOCH.
 *
 * @return Tempo em milisegundos
 */
rtime_t timestamp(void);

/**
 * @brief Retornar um marcador no formato aceito pelo LIKWID.
 *
 * @param baseName Nome do marcador (EX: ABC).
 * @param n Número para segunda parte do marcador (EX: 10).
 *
 * @return String no formato de marcador (EX: ABC_10)
 */
string_t markerName(string_t baseName, int n);

void read_input(int *n, int *k, real_t *w, int *maxit, real_t *epsilon);

void fill_zeros_matrix(real_t **m, int n);

void fill_zeros_vector(real_t *v, int n);

void generate_identity(real_t **m, int n);

real_t dot_product(real_t *v1, real_t *v2, int n);

void matrix_times_vector(real_t **m, int n, real_t *v, real_t *rv);

#endif // __UTILS_H__

