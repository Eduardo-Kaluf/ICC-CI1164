//#include <likwid.h>

#include <stdio.h>

#include "utils.h"
#include "sislin.h"
#include "eliminacaoGauss.h"

int main() {
    SistLinear_t *input = lerSisLin();

    triangulariza(input);

    prnSisLin(input);
    liberaSisLin(input);

    return 0;
}
