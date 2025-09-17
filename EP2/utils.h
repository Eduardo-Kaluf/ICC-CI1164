// EDUARDO KALUF - GRR 20241770

#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define MAX_ITER 100
#define NORMA_STOP 1e-5

// Valor absoluto de um número real. Alternativa ao uso da função 'fabs()'
#define ABS(num)  ((num) < 0.0 ? -(num) : (num))

// real_t: tipo usado para representar valores em ponto flutuante
typedef double real_t;

// string_t: tipo usado para representar ponteiros para char/strings
typedef char * string_t;

// rtime_t: tipo usado para representar valores de tempo em ponto flutuante
typedef double rtime_t;

// lint_t: tipo usado para representar valores long int
typedef long long int lint_t;

// Número máximo de dígitos em um número inteiro
#define numDigits(n)  6  // ( n ? (int) log10(ABS(n)) + 1 : 1 )

// Macro para verificar de valor 'n' é potência de 2 ou não.
// 'n' DEVE ser positivo e não-nulo
#define isPot2(n) (!(n & (n - 1)))     // #define isPot2(n) (n && !(n & (n - 1)))

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

/**
 * @brief Imprime um vetor na tela.
 *
 * @param v Vetor a ser impresso.
 * @param n Tamanho do vetor.
 */
void print_vetor(real_t *v, int n);

/**
 * @brief Zera o vetor passado.
 *
 * @param v Vetor a ser impresso.
 * @param n Tamanho do vetor.
 */
void zera_vetor(real_t *v, int n);

#endif // __UTILS_H__

