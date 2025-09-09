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

// TODO TODO TODO ADD OPTION TO READ MORE LINES
int main() {
	fesetround(FE_DOWNWARD);

	EDo *edo = read_edo();
	Tridiag *tridiag = genTridiag(edo);

	const int n = tridiag->n;
	real_t *X = malloc(sizeof(real_t) * n);

	rtime_t tempo = timestamp();

	#ifdef TESTE
		LIKWID_MARKER_INIT;
		LIKWID_MARKER_START("EDO_TEST");
	#endif

	gaussSeidel_3Diag(tridiag, X, MAX_ITER);

	#ifdef TESTE
		LIKWID_MARKER_STOP("EDO_TEST");
		LIKWID_MARKER_CLOSE;
	#endif

	tempo = timestamp() - tempo;

	prnEDOsl(edo);
	printf("\n");
	print_vector(X, n);
	printf("%16.8e", tempo);
	printf("\n");

	// free_tridiag(tridiag);
	// free(edo);
	// free(X);

    return 0;
}
