#ifndef __VETOR_H__
#define __VETOR_H__

#include "utils.h"

enum ALLOC_TYPE {
    USE_CALLOC,
    USE_MALLOC
};


/**
 * @brief Retorna o valor do produto do produto escalar entre dois vetores
 *
 * @param v1 Ponteiro para o primeiro vetor
 * @param v2 Ponteiro para o segundo vetor
 * @param n Tamanho dos vetores
 */
real_t dot_product(real_t *v1, real_t *v2, int n);

/**
 * @brief Exibe o vetor na tela com format "%.16g"
 *
 * @param v Ponteiro para o vetor
 * @param n Tamanho do vetor
 */
void print_vector(real_t *v, int n);

/**
 * @brief Multiplica um escalar por um vetor e soma este resultado no destino
 *
 * @param v Ponteiro para o vetor
 * @param n Tamanho do vetor
 * @param value Escalar a ser multiplicado
 * @param dest Ponteiro onde o resultado será somado
 */
void sum_vector_times_scalar(real_t *v, int n, real_t value, real_t *dest);

/**
 * @brief Copia o vetor src para o vetor dest
 *
 * @param dest Ponteiro para o vetor de destino
 * @param src Ponteiro para o vetor a ser copiado
 * @param n Tamanho dos vetores
 */
void copy_vector(real_t *dest, real_t *src, int n);


/**
 * @brief Aloca um vetor fazendo as verificações de segurança necessárias
 *
 * @param type Tipo de alocação que será realizada
 * @param size Tamanho do tipo que será alocado
 * @param n Tamanho do vetor
 *
 * @return Ponteiro para o vetor alocado
 */
void* alloc_single_vector(enum ALLOC_TYPE type, int size, int n);

#endif // __VETOR_H__
