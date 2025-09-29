#include <stdlib.h>

#include "sislin.h"
#include "utils.h"


int main() {
    srandom(20252);

    int n, k, maxit;
    real_t w, epsilon;

    read_input(&n, &k, &w, &maxit, &epsilon);

    printf("%d, %d, %f, %d, %f", n, k, w, maxit, epsilon);

    return 0;
}
