// EDUARDO KALUF - GRR 20241770
#include <fenv.h>
#include <stdio.h>
#include <stdlib.h>

#include "edo.h"

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

int main() {
	fesetround(FE_DOWNWARD);

	EDo *edo = read_edo();

	prnEDOsl(edo);

	Tridiag *tridiag = genTridiag(edo);



	free(edo);

    return 0;
}
