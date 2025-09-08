// EDUARDO KALUF - GRR 20241770
#include <fenv.h>
#include <stdio.h>
#include <stdlib.h>

#include "edo.h"
#include "fatoracao_lu.h"
#include "utils.h"

// TODO TODO TODO
// SEE IF IT NEEDS TO READ MORE LINES
// EXAMPLE ON THE TEST.DAT IT INPUTS 0 0 0 0 and then 0 0 1 0
EDo* read_edo() {
	EDo *edo = malloc(sizeof(EDo));
	if (edo == NULL)
		return NULL;

	scanf("%d", &edo->n);
	scanf("%lf %lf", &edo->a, &edo->b);
	scanf("%lf %lf", &edo->ya, &edo->yb);
	scanf("%lf %lf", &edo->p, &edo->q);
	scanf("%lf %lf %lf %lf", &edo->r1, &edo->r2, &edo->r3, &edo->r4);

	return edo;
}

void printMatrix(int rows, int cols, double matrix[rows][cols]) {
	printf("Displaying the Matrix:\n");
	// Loop through each row
	for (int i = 0; i < rows; i++) {
		// Loop through each column in the current row
		for (int j = 0; j < cols; j++) {
			// Print the element followed by a tab for spacing
			printf("%f\t", matrix[i][j]);
		}
		// Move to the next line after printing all columns in a row
		printf("\n");
	}
}

void printTridiagMatrix(const Tridiag *A) {
	if (A == NULL || A->D == NULL || A->Di == NULL || A->Ds == NULL) {
		printf("Erro: A estrutura da matriz ou seus vetores não foram inicializados.\n");
		return;
	}

	printf("Matriz Tridiagonal (formato %d x %d):\n", A->n, A->n);

	// Laço para percorrer as linhas
	for (int i = 0; i < A->n; i++) {
		// Laço para percorrer as colunas
		for (int j = 0; j < A->n; j++) {
			// 1. Verifica se está na diagonal principal (i == j)
			if (i == j) {
				printf("%8.3f ", A->D[i]);
			}
			// 2. Verifica se está na diagonal superior (j == i + 1)
			else if (j == i + 1) {
				printf("%8.3f ", A->Ds[i]);
			}
			// 3. Verifica se está na diagonal inferior (j == i - 1)
			else if (j == i - 1) {
				// O índice de Di corresponde ao da coluna (j) ou linha-1 (i-1)
				printf("%8.3f ", A->Di[j]);
			}
			// 4. Se não estiver em nenhuma das diagonais, é zero
			else {
				printf("%8.3f ", 0.0);
			}
		}
		// Pula para a próxima linha ao final de cada linha da matriz
		printf("\n");
	}
}

int main() {
	fesetround(FE_DOWNWARD);
	double matrix[5][5] = {
		{-1.725844322818500e+00, 1.0e+00, 0.0e+00, 0.0e+00, 0.0e+00},
		{ 1.0e+00, -1.725844322818500e+00, 1.0e+00, 0.0e+00, 0.0e+00},
		{ 0.0e+00,  1.0e+00, -1.725844322818500e+00, 1.0e+00, 0.0e+00},
		{ 0.0e+00,  0.0e+00,  1.0e+00, -1.725844322818500e+00, 1.0e+00},
		{ 0.0e+00,  0.0e+00,  0.0e+00,  1.0e+00, -1.725844322818500e+00}
	};
	double X[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
	double B[5] = {-2.0, 0.0, 0.0, 0.0, 2.0};

	double Z[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

	EDo *edo = read_edo(); //prnEDOsl(edo);
	Tridiag *tridiag = genTridiag(edo);

	fatoracaoLuTridiag(tridiag, tridiag->n);
	printTridiagMatrix(tridiag);

	resolveSlTridiag(tridiag, Z);
	print_array(Z, 5);

	// __________ //

	fatoracaoLU(5, matrix);
	printMatrix(5, 5, matrix);

	resolveSL(5, matrix, B, X);
	print_array(X, 5);

	printf("\n FIM \n");
	free(edo);

    return 0;
}
