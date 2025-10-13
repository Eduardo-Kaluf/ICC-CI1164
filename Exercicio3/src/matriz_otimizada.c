#include "matriz_otimizada.h"

void multMatVetOtimizada(MatRow mat, Vetor v, int m, int n, Vetor res) {
    for (int i = 0; i < m; ++i)
        res[i] = 0.0;

    for (int i = 0; i < m - m % UF; i += UF) {
        for (int j = 0; j < n; j++) {
            res[i]     += mat[i * n + j] * v[j];
            res[i + 1] += mat[(i + 1) * n + j] * v[j];
            res[i + 2] += mat[(i + 2) * n + j] * v[j];
            res[i + 3] += mat[(i + 3) * n + j] * v[j];
        }
    }

    for (int i = m - m % UF; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            res[i] += mat[i * n + j] * v[j];
        }
    }
}

void multMatMatOtimizada(MatRow A, MatRow B, int n, MatRow C) {
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n - n % UF; j += UF) {

            C[i * n + j] = C[i * n + j + 1] = C[i * n + j + 2] = C[i * n + j + 3] = 0.0;

            for (int k=0; k < n; ++k) {
                C[i * n + j    ] += A[i * n + k] * B[k * n + j    ];
                C[i * n + j + 1] += A[i * n + k] * B[k * n + j + 1];
                C[i * n + j + 2] += A[i * n + k] * B[k * n + j + 2];
                C[i * n + j + 3] += A[i * n + k] * B[k * n + j + 3];
            }
        }

        for (int j = n - n % UF; j < n; ++j) {
            C[i * n + j] = 0.0;

            for (int k = 0; k < n; ++k)
                C[i * n + j] += A[i * n + k] * B[k * n + j];
        }
    }
}
