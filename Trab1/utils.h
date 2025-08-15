#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <time.h>

#define TESTS_QUANTITY 3
#define CALC_QUANTITY 2

enum CriteriosDeParada {
    RELATIVE_ERROR_TEST,
    EPSILON_TEST,
    ULP_TEST
};

enum CalcType {
    FAST,
    SLOW
};

typedef double real_t;
typedef double rtime_t;
typedef char * string_t;

double timestamp(void);

#endif // __UTILS_H__

