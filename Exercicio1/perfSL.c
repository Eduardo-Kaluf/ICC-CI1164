//#include <likwid.h>

#include <stdio.h>

#include "utils.h"
#include "sislin.h"
int main() {
    SistLinear_t *input = lerSisLin();

    prnSisLin(input);   
    liberaSisLin(input);

    return 0;
}
