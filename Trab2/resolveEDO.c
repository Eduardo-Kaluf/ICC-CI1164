// EDUARDO KALUF - GRR 20241770

#ifdef TESTE
	#include <likwid.h>
#endif

#include <fenv.h>
#include <stdio.h>
#include <stdlib.h>

#include "edo.h"
#include "fatoracao_lu.h"
#include "utils.h"

// TODO TODO TODO
// SEE IF IT NEEDS TO READ MORE LINES
// EXAMPLE ON THE TEST.DAT IT INPUTS 0 0 0 0 and then 0 0 1 0

int main() {
	fesetround(FE_DOWNWARD);

	#ifdef TESTE
		printf("TESTE");
	#endif


	EDo *edo = read_edo();
	Tridiag *tridiag = genTridiag(edo);

	const int n = tridiag->n;
	real_t *X = malloc(sizeof(real_t) * n);

	rtime_t tempo = timestamp();
	#ifdef TESTE
		printf("\n\n\n\nTESTE");

		LIKWID_MARKER_INIT;
		LIKWID_MARKER_START("EDO_TEST");
	#endif

	fatoracaoLuTridiag(tridiag, n);
	resolveSlTridiag(tridiag, X);


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
