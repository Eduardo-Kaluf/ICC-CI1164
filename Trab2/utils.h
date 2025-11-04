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
 * @brief Realiza a leitura dos inputs base do programa
 *
 * @param n Dimensão das matrizes e tamanho dos vetores do programa
 * @param k Número de diagonais da matriz
 * @param w Seletor do pré-condicionador
 * @param maxit Número máximo de iterações
 * @param epsilon Erro aproximado absoluto máximo
 */
void read_input(int *n, int *k, real_t *w, int *maxit, real_t *epsilon);


/**
 * @brief Aloca vetores necessários para o programa
 *
 * @param X Vetor Solução
 * @param B Vetor de termos independentes
 * @param BSP Vetor B após modificação para matriz simétrica e positiva
 * @param n Tamanho dos vetores
 */
void alloc_vectors(real_t **X, real_t **B, real_t **BSP, int n);


/**
 * @brief Aloca matrizes necessários para o programa
 *
 * @param A Matriz principal
 * @param ASP Matriz principal após modificação para matriz simétrica e positiva
 * @param M Matriz do pré-condicionador
 * @param D Diagonal da matriz principal
 * @param L Parte inferior da matriz principal
 * @param U Parte superior da matriz principal
 * @param n Dimensão das matrizes
 */
void alloc_matrixes(real_t ***A, real_t ***ASP, real_t ***M, real_t ***D, real_t ***L, real_t ***U, int n);

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
 * @brief Libera a memória das matrizes e vetores alocados de maneira segura
 *
 * @param X Vetor solução
 * @param B Vetor de termos independentes
 * @param BSP Vetor B após modificação para matriz simétrica e positiva
 * @param A Matriz principal
 * @param ASP Matriz principal após modificação para matriz simétrica e positiva
 * @param M Matriz do pré-condicionador
 * @param D Diagonal da matriz principal
 * @param L Parte inferior da matriz principal
 * @param U Parte superior da matriz principal
 * @param n Dimensão das matrizes
 */
void free_all_memory(real_t **X, real_t **B, real_t **BSP, real_t ***A, real_t ***ASP, real_t ***M, real_t ***D, real_t ***L, real_t ***U, int n);

/**
 * @brief Exibe uma mensagem de erro fatal e encerra o programa graciosamente
 *
 * @param message Mensagem de erro exibida ao usuário
 */
void handle_error(char *message) __attribute__((__noreturn__));

#endif // __UTILS_H__
