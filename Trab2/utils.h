#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>

// Valor absoluto de um número. Alternativa ao uso da função 'fabs()'
#define ABS(num)  ((num) < 0.0 ? -(num) : (num))
// Quantidade de inputs que serão lidos
#define N_INPUTS 5

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

int max (int a, int b);
// TODO TODO TODO TRANSFORM INTO INLINE FUNCTION
int min (int a, int b);

#define K 7
#define OFF_SET 12

#define SP_K 13
#define SP_OFF_SET 42

#define BAND_WIDTH K / 2

#define MAX_IT 25

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
 * @brief Aloca vetores necessários para o programa
 *
 * @param X Vetor Solução
 * @param M Vetor pré-condicionador
 * @param n Tamanho dos vetores
 */
void alloc_vectors(real_t **X, real_t **M, int n);

/**
 * @brief Exibe os resultados do programa
 *
 * @param n Tamanho do vetor
 * @param X Vetor solução
 * @param norm Norma máxima do erro aproximado em x após última iteração
 * @param residuo Norma euclidiana do resíduo
 * @param time_pc Tempo do pré-condicionador
 * @param time_iter Tempo médio de uma iteração do método
 * @param time_residuo Tempo para calcular a norma euclidiana do resíduo
 */
void print_results(int n, real_t *X, real_t norm, real_t residuo, rtime_t time_pc, rtime_t time_iter, rtime_t time_residuo);


/**
 * @brief Exibe uma mensagem de erro fatal e encerra o programa graciosamente
 *
 * @param message Mensagem de erro exibida ao usuário
 */
void handle_error(char *message) __attribute__((__noreturn__));

#endif // __UTILS_H__
