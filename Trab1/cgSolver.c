#include <stdlib.h>

#include "sislin.h"
#include "utils.h"


int main() {
    srandom(20252);

    int n, k, maxit;
    real_t omega, epsilon;

    read_input(&n, &k, &omega, &maxit, &epsilon);

    printf("%d, %d, %f, %d, %f", n, k, omega, maxit, epsilon);

    return 0;
}
