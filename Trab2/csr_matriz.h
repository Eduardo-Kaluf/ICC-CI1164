#ifndef __CSR_MATRIZ_H__
#define __CSR_MATRIZ_H__

#include "utils.h"


typedef struct csr {
    real_t * values;
    int *col_ind;
    int *row_ptr;
    int n;
    real_t *B;
} csr;

enum MODE {
    CSR_MODE,
    STANDARD_MODE
};


/**
 * @brief Aloca uma matriz CSR
 *
 * @param n Dimensão da matriz
 * @param nnz_capacity Quantidade de elementos não nulos na matriz
 *
 * @return Matriz CSR devidamente alocada
 */
csr* alloc_csr(int n, int nnz_capacity);

/**
 * @brief Aloca uma matriz CSR
 *
 * @param c Matriz k-diagonal guardada como CSR
 * @param mode Modo como a matriz será exibida:
 *      - CSR_MODE: Imprime a matriz como três vetores:
 *          - Vetor de valores
 *          - Vetor de ponteiro para linhas
 *          - Vetor de índices das colunas
 *      - STANDARD_MODE: Imprime a matriz como se ela fosse uma matriz nxn normal, preenchendo zeros onde não tem nada guardado
 */
void print_csr(csr *c, enum MODE mode);

/**
 * @brief Transpoe uma matriz CSR
 *
 * @param c Matriz k-diagonal guardada como CSR
 *
 * @return A matriz CSR transposta
*/
csr* csr_transpose(const csr *c);

/**
 * @brief Multiplica uma matriz CSR por um vetor
 *
 * @param c Matriz k-diagonal guardada como CSR
 * @param src Vetor a ser multiplicado
 * @param dest Vetor que guardará o resultado
*/
void csr_time_vector(csr *c, real_t *src, real_t *dest);

#endif // __CSR_MATRIZ_H__
