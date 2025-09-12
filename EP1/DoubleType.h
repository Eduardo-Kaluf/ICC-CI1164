#ifndef __DOUBLE_TYPE_H__
#define __DOUBLE_TYPE_H__


#include <stdint.h>
#include <float.h>

typedef union {
    uint64_t i;
    double f;
    struct {                    // Bitfields for exploration (64 bits = sign|exponent|mantissa)
        uint64_t mantissa : 52; // primeiros 52 bits (da direita para a esquerda)
        uint64_t exponent : 11; // próximos 11 bits
        uint64_t sign : 1;      // proximo bit (ou seja, o bit mais a esquerda)
    } parts;
} Double_t;

#endif // __DOUBLE_TYPE_H__
