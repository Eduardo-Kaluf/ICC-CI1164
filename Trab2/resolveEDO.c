// EDUARDO KALUF - GRR 20241770

#ifdef TESTE
	#include <likwid.h>
#endif

#include <fenv.h>
#include <stdio.h>
#include <stdlib.h>

#include "edo.h"
#include "utils.h"
#include "gauss_seidel.h"

int main() {
	fesetround(FE_DOWNWARD);

	EDo *edo = read_edo();

	const int n = edo->n;

	// Vetor solução
	real_t *Y = malloc(sizeof(real_t) * edo->n);

	int it;
	real_t norma;

	do {
		// Geramos uma tridiagonal nova para cada nova leitura de coeficientes (r1, r2, r3, r4)
		Tridiag *tridiag = genTridiag(edo);

		rtime_t tempo = timestamp();

		#ifdef LIKWID_TEST
			LIKWID_MARKER_INIT;
			LIKWID_MARKER_START("EDO_TEST");
		#endif

		it = gaussSeidel_3Diag(tridiag, Y, MAX_ITER, &norma);

		#ifdef LIKWID_TEST
			LIKWID_MARKER_STOP("EDO_TEST");
			LIKWID_MARKER_CLOSE;
		#endif

		tempo = timestamp() - tempo;

		// Printando os resultados
		prnEDOsl(edo);
		print_vetor(Y, n);
		printf("%d\n%23.15e\n%16.8e\n\n", it, norma, tempo);

		// Zeramos o vetor solução para cada nova leitura a fim de que o teste não tenha nenhum pre redirecionamento
		zera_vetor(Y, n);

		free_tridiag(tridiag);

	} while (scanf("%lf %lf %lf %lf", &edo->r1, &edo->r2, &edo->r3, &edo->r4) != EOF);

	free(edo);
	free(Y);

    return 0;
}
