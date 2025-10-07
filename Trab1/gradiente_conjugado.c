#include "gradiente_conjugado.h"

#include <string.h>
#include "sislin.h"

real_t calc_norm(real_t *X, real_t *X_old, int n) {
    real_t norm_max = 0.0;

    for (int i = 0; i < n; i++) {
        real_t current_norm = fabs(X_old[i] - X[i]);

        if (current_norm > norm_max)
            norm_max = current_norm;
    }

    return norm_max;
}

// real_t calc_gradiente_conjugado(real_t **A, real_t *B, real_t *X, real_t **M, int n, int maxit, double epsilon, rtime_t *tempo) {
//     int i;
//     int size = n * sizeof(real_t);

//     real_t *X_old = calloc(n, sizeof(real_t));

//     real_t *R = malloc(size);
//     memcpy(R, B, size);

//     real_t *V = malloc(n * sizeof(real_t));
//     matrix_times_vector(M, n, B, V);

//     real_t *Y = malloc(n * sizeof(real_t));
//     matrix_times_vector(M, n, R, Y);

//     real_t aux = dot_product(Y, R, n);

//     real_t *Z = malloc(n * sizeof(real_t));

//     *tempo = timestamp();
//     for (i = 0; i < maxit; i++) {
//         matrix_times_vector(A, n, V, Z); //z = Av
        
//         //n deveria ser V transposta?
//         real_t s = aux / dot_product(V, Z, n);

//         for (int j = 0; j < n; j++)
//             X[j] += s * V[j];

//         for (int j = 0; j < n; j++)
//             R[j] -= s * Z[j];

//         matrix_times_vector(M, n, R, Y);

//         if (dot_product(R, R, n) < epsilon)
//             break;

//         for (int j = 0; j < n; j++)
//             X_old[j] = X[j];

//         real_t aux1 = dot_product(Y, R, n);

//         real_t m = aux1 / aux;

//         aux = aux1;

//         for (int j = 0; j < n; j++)
//             V[j] = Y[j] + m * V[j];
//     }

//     *tempo = (timestamp() - *tempo) / i;

//     real_t norm = calc_norm(X, X_old, n);

//     free(R);
//     free(V);
//     free(Z);
//     free(Y);
//     free(X_old);

//     return norm;
// }

// void Jacobi (real_t *V1, real_t V2, int n) {

//     for(int i )
// }
void ssor(real_t **A, real_t *R, real_t *Y, int n, real_t w) {
    real_t *aux = calloc(n, sizeof(real_t));

    // foward: (D + ωL) y = ωD r
    for (int i = 0; i < n; i++) {
        real_t soma = 0.0;
        for (int j = 0; j < i; j++)
            soma += A[i][j] * aux[j];
        aux[i] = (A[i][i] * R[i] - w * soma) / (A[i][i]);
    }

    memset(Y, 0, n * sizeof(real_t));
    // backward: (D + ωU) Y = ωD y
    for (int i = n - 1; i >= 0; i--) {
        real_t soma = 0.0;
        for (int j = i + 1; j < n; j++)
            soma += A[i][j] * Y[j];
        Y[i] = (aux[i] - w * soma) / (A[i][i]);
    }

    free(aux);
}

void jacobi(real_t **A, real_t *R, real_t *V, int n){

    for(int i = 0; i < n; i++){
        V[i] = R[i] / A[i][i];
    }
}

void precondicionador(real_t **A, real_t *R, real_t *Y, int n, real_t w){
    
    if(w == 0.0) {
        jacobi(A, R, Y, n);
    } else if(w == -1.0){
        printf("aaaa\n");
        memcpy(Y, R, n * sizeof(real_t));
    } else {
        ssor(A, R, Y, n, w);
    } 
}


real_t calc_gradiente_conjugado(real_t **A, real_t *B, real_t *X, int n, int maxit, double epsilon, rtime_t *tempo, real_t w) {
    int i;
    int size = n * sizeof(real_t);

    real_t *X_old = calloc(n, sizeof(real_t));

    real_t *R = malloc(size);
    memcpy(R, B, size);

    real_t *V = malloc(n * sizeof(real_t));
    
    //matrix_times_vector(M, n, B, V);
    
    // for(int i = 0; i < n; i++){
    //     V[i] = B[i] * D[i];
    // }
    precondicionador(A, B, V, n, w);

    real_t *Y = malloc(n * sizeof(real_t));
    //matrix_times_vector(M, n, R, Y);
    
    // for(int i = 0; i < n; i++){
    //     Y[i] = R[i] * D[i];
    // }

    precondicionador(A, R, Y, n, w);
    //NÃO DEVERIA SER A TRANSPOSTA???????
    real_t aux = dot_product(Y, R, n);

    real_t *Z = malloc(n * sizeof(real_t));

    *tempo = timestamp();
    for (i = 0; i < maxit; i++) {
        matrix_times_vector(A, n, V, Z); //z = Av
        
        //n deveria ser V transposta?
        real_t s = aux / dot_product(V, Z, n);

        for (int j = 0; j < n; j++){
            X[j] += s * V[j];
            R[j] -= s * Z[j];
        }
        
        //matrix_times_vector(M, n, R, Y);
        
        // for(int j = 0; j < n; j++){
        //     Y[j] = R[j] * D[j];
        // }
        
        precondicionador(A, R, Y, n, w);

        if (dot_product(R, R, n) < epsilon)
            break;

        for (int j = 0; j < n; j++)
            X_old[j] = X[j];

        real_t aux1 = dot_product(Y, R, n);

        real_t m = aux1 / aux;

        aux = aux1;

        for (int j = 0; j < n; j++)
            V[j] = Y[j] + m * V[j];
    }

    *tempo = (timestamp() - *tempo) / i;

    real_t norm = calc_norm(X, X_old, n);

    free(R);
    free(V);
    free(Z);
    free(Y);
    free(X_old);

    return norm;
}
