#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>

#include "sislin.h"
#include "utils.h"


int compare_doubles(real_t a, real_t b) {
    return fabs(a - b) < 1e-9;
}

real_t generateRandomA(int i, int j, int k) {
    return (real_t)( (i+1) * 10 + (j+1) );
}

real_t generateRandomB(int k) {
    return (real_t)(k * 10.0);
}

// Aloca memória para uma matriz n x n
real_t **allocate_matrix(int n) {
    real_t **m = (real_t **)malloc(n * sizeof(real_t *));
    if (m == NULL) return NULL;
    for (int i = 0; i < n; i++) {
        m[i] = (real_t *)malloc(n * sizeof(real_t));
        if (m[i] == NULL) {
            // Em caso de falha, libera o que já foi alocado
            for (int k = 0; k < i; k++) free(m[k]);
            free(m);
            return NULL;
        }
    }
    return m;
}

// Libera a memória alocada para a matriz
void free_matrix(real_t **m, int n) {
    for (int i = 0; i < n; i++) {
        free(m[i]);
    }
    free(m);
}

// Imprime uma matriz
void print_matrix(const char* title, real_t **m, int n) {
    printf("%s\n", title);
    for (int i = 0; i < n; i++) {
        printf("[ ");
        for (int j = 0; j < n; j++) {
            printf("%4.1f ", m[i][j]);
        }
        printf("]\n");
    }
    printf("\n");
}

// Imprime um vetor
void print_vector(const char* title, real_t *v, int n) {
    printf("%s\n[ ", title);
    for (int i = 0; i < n; i++) {
        printf("%4.1f ", v[i]);
    }
    printf("]\n\n");
}

// --- Funções de Teste ---

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "sislin.h"
#include "utils.h"

// --- Test Functions ---

void test_fill_zeros() {
    printf("--- Teste: fill_zeros_matrix e fill_zeros_vector ---\n");
    int n = 3;

    // Test matrix
    real_t **m = allocate_matrix(n);
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) m[i][j] = (real_t)(i + j + 1.0);
    print_matrix("Matriz Antes:", m, n);
    fill_zeros_matrix(m, n);
    print_matrix("Matriz Depois:", m, n);

    // Test vector
    real_t v[] = {5.0, 10.0, 15.0};
    print_vector("Vetor Antes:", v, n);
    fill_zeros_vector(v, n);
    print_vector("Vetor Depois:", v, n);

    free_matrix(m, n);
}

void test_generate_identity() {
    printf("--- Teste: generate_identity ---\n");
    int n = 4;
    real_t **id = allocate_matrix(n);
    generate_identity(id, n);
    print_matrix("Matriz Identidade Gerada (4x4):", id, n);

    int success = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!compare_doubles(id[i][j], (i == j) ? 1.0 : 0.0)) {
                success = 0; break;
            }
        }
        if (!success) break;
    }
    printf("VERIFICAÇÃO: %s\n\n", success ? "APROVADO ✅" : "FALHOU ❌");
    free_matrix(id, n);
}

void test_dot_product() {
    printf("--- Teste: dot_product ---\n");
    int n = 3;
    real_t v1[] = {1.0, 2.0, 3.0};
    real_t v2[] = {4.0, 5.0, 6.0};
    print_vector("Vetor 1:", v1, n);
    print_vector("Vetor 2:", v2, n);
    real_t result = dot_product(v1, v2, n);
    real_t expected = 32.0;
    printf("Resultado do Produto Escalar: %.2f\n", result);
    printf("Resultado Esperado: %.2f\n", expected);
    printf("VERIFICAÇÃO: %s\n\n", compare_doubles(result, expected) ? "APROVADO ✅" : "FALHOU ❌");
}

void test_matrix_times_vector() {
    printf("--- Teste: matrix_times_vector ---\n");
    int n = 3;
    real_t **m = allocate_matrix(n);
    m[0][0]=1; m[0][1]=2; m[0][2]=3;
    m[1][0]=4; m[1][1]=5; m[1][2]=6;
    m[2][0]=7; m[2][1]=8; m[2][2]=9;
    real_t v[] = {2.0, 3.0, 4.0};
    real_t rv[n];
    print_matrix("Matriz M:", m, n);
    print_vector("Vetor V:", v, n);

    matrix_times_vector(m, n, v, rv);
    print_vector("Vetor Resultante (M * V):", rv, n);
    real_t expected_rv[] = {20.0, 47.0, 74.0};
    print_vector("Vetor Esperado:", expected_rv, n);
    int success = compare_doubles(rv[0], expected_rv[0]) && compare_doubles(rv[1], expected_rv[1]) && compare_doubles(rv[2], expected_rv[2]);
    printf("VERIFICAÇÃO: %s\n\n", success ? "APROVADO ✅" : "FALHOU ❌");
    free_matrix(m, n);
}

void test_criaKDiagonal() {
    printf("--- Teste: criaKDiagonal ---\n");
    int n = 4, k = 3;
    real_t **A = allocate_matrix(n);
    real_t B[n];
    criaKDiagonal(n, k, A, B);
    print_matrix("Matriz A (k=3) Gerada:", A, n);
    print_vector("Vetor B Gerado:", B, n);

    free_matrix(A, n);
}

void test_genSimetricaPositiva() {
    printf("--- Teste: genSimetricaPositiva (n=5, Tridiagonal) ---\n");
    int n = 5;
    rtime_t tempo;
    real_t **A = allocate_matrix(n);

    // Initialize with zeros, then create a tridiagonal matrix
    fill_zeros_matrix(A, n);
    for (int i = 0; i < n; i++) {
        A[i][i] = 2.0;
        if (i > 0) A[i][i-1] = -1.0;
        if (i < n - 1) A[i][i+1] = -1.0;
    }

    real_t b[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    real_t **ASP = allocate_matrix(n);
    real_t bsp[n];

    print_matrix("Matriz A (Entrada):", A, n);
    print_vector("Vetor b (Entrada):", b, n);

    genSimetricaPositiva(A, b, n, 3, ASP, bsp, &tempo);
    print_matrix("Matriz ASP (A^T * A):", ASP, n);
    print_vector("Vetor bsp (A^T * b):", bsp, n);

    // Expected results for the tridiagonal matrix.
    // Since A is symmetric, A^T = A, so ASP = A * A and bsp = A * b.
    real_t expected_ASP[5][5] = {
        { 5.0, -4.0,  1.0,  0.0,  0.0},
        {-4.0,  6.0, -4.0,  1.0,  0.0},
        { 1.0, -4.0,  6.0, -4.0,  1.0},
        { 0.0,  1.0, -4.0,  6.0, -4.0},
        { 0.0,  0.0,  1.0, -4.0,  5.0}
    };
    real_t expected_bsp[] = {0.0, 0.0, 0.0, 0.0, 6.0};

    int success = 1;
    for (int i = 0; i < n; i++) {
        if (!compare_doubles(bsp[i], expected_bsp[i])) {
            success = 0;
            break;
        }
        for (int j = 0; j < n; j++) {
            if (!compare_doubles(ASP[i][j], expected_ASP[i][j])) {
                success = 0;
                break;
            }
        }
        if (!success) break;
    }

    printf("VERIFICAÇÃO: %s\n\n", success ? "APROVADO ✅" : "FALHOU ❌");
    free_matrix(A, n);
    free_matrix(ASP, n);
}

void test_geraDLU() {
    printf("--- Teste: geraDLU ---\n");
    int n = 4, k = 3;
    rtime_t tempo;
    real_t **A = allocate_matrix(n), **D = allocate_matrix(n), **L = allocate_matrix(n), **U = allocate_matrix(n);

    real_t temp_b[n];
    fill_zeros_vector(temp_b, n);

    criaKDiagonal(n, k, A, temp_b);
    print_matrix("Matriz A de Entrada:", A, n);
    geraDLU(A, n, k, D, L, U, &tempo);
    print_matrix("Matriz D (Diagonal):", D, n);
    print_matrix("Matriz L (Inferior):", L, n);
    print_matrix("Matriz U (Superior):", U, n);

    int success = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!compare_doubles(A[i][j], D[i][j] + L[i][j] + U[i][j])) {
                success = 0; break;
            }
        }
        if (!success) break;
    }
    printf("VERIFICAÇÃO (D+L+U == A): %s\n\n", success ? "APROVADO ✅" : "FALHOU ❌");
    free_matrix(A, n); free_matrix(D, n); free_matrix(L, n); free_matrix(U, n);
}

int main() {
    printf("=======================================\n");
    printf("   INICIANDO SCRIPT DE TESTE   \n");
    printf("=======================================\n\n");

    test_fill_zeros();
    test_generate_identity();
    test_dot_product();
    test_matrix_times_vector();
    test_criaKDiagonal();
    test_genSimetricaPositiva();
    test_geraDLU();

    printf("=======================================\n");
    printf("       TESTES CONCLUÍDOS       \n");
    printf("=======================================\n");

    return 0;
}
