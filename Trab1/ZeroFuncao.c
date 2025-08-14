#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

// ********* RETORNO DAS FUNÇÕES DEVE SER O VALOR CALCULADO DO CRITERIO DE PARADA (CRITERIO DE PARADA <----> RETORNO)

getCriterioDeParada(enum CriterioDeParada) {
    switch (criterioDeParada)
}




// Retorna valor do erro quando método finalizou. Este valor depende de tipoErro
real_t newtonRaphson (Polinomio p, real_t x0, int criterioParada, int *it, real_t *raiz) {
    // x0 -> x0
    // double f(double x) -> calcPolinomio_rapido/calcPolinomio_lento (p, x)
    // phi -> x - px / dpx (que vem do calcpolinomio)

    raiz_t x_new = x0;
    raiz_t x_old;
    raiz_t px, dpx;


    do {
        x_old = x_new;
        calcPolinomio_rapido(p, x_old, px, dpx);
        x_new = x_old - (px / dpx);

        it++
    } while (/* CRITERIO DE PARADA FUNCTION */)

    return fabs((xm_new - xm_old) / xm_new);
}


// Retorna valor do erro quando método finalizou. Este valor depende de tipoErro
real_t bisseccao (Polinomio p, real_t a, real_t b, int criterioParada, int *it, real_t *raiz) {

    // xl -> a
    // xu -> b
    // double f(double x) -> calcPolinomio_rapido/calcPolinomio_lento (p)
    // epsilon -> DBL_EPSILON (CONSTANTE)
    // return da bissecao -> raiz

    // criterioParada (Á PARTE)
    // it (Á PARTE)

    switch (criterioParada) {
        // RETURN CRITERIO DE PARADA FUNCTION
    }

    real_t xm_old, xm_new;
    real_t px1, dpx1, px2, dpx2, val;

    xm_new = (a + b) / 2;
    calcPolinomio_rapido(p, a, px1, dpx1);
    calcPolinomio_rapido(p, xm_new, px2, dpx2)
    val = px1 * px2;

    it++;

    if (val < 0)
        b = xm_new;
    else if (val > 0)
        a = xm_new
    else
        /* raiz = xm_new */
        return 0;
    
    do {
        it++;
        xm_old = xm_new;
        xm_new = (a + b) / 2;

        calcPolinomio_rapido(p, a, px1, dpx1);
        calcPolinomio_rapido(p, xm_new, px2, dpx2)
        val = px1 * px2;

        if (val < 0)
            b = xm_new;
        else if (val > 0)
            a = xm_new
        else
            return xm_new;
    } while (/* CRITERIO DE PARADA FUNCTION */)

    return fabs((xm_new - xm_old) / xm_new);
}


void calcPolinomio_rapido(Polinomio p, real_t x, real_t *px, real_t *dpx) {
    real_t b = 0;
    real_t c = 0;

    for (int i = p.grau; i > 0; --i) {
        b = b*x + p.->p[i];
        c = c*x + b;
    }
    b = b*x + p->p[0];
    *px = b;
    *dpx = c;
}

void calcPolinomio_lento(Polinomio p, real_t x, real_t *px, real_t *dpx) {
    for (int i = p.grau; i >= 0; i --)
        px += p->p[i] * pow(x, i);
 
    for (int i = p.grau; i >= 1; i --)
        dpx += p->p[i] * i * pow(x, i - 1);
}
