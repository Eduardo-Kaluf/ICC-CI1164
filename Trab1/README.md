# SERGIO SIVONEI DE SANT'ANA FILHO GRR20242337
# EDUARDO KALUF GRR20241770


### CALCULAMOS A O TEMPO DE GERAR AS CONDICIONAIS JÁ GERANDO A MATRIZ INVERSA



    n: (n>10)  a dimensão do Sistema Linear.
    k: (k>1 e k ímpar)  o número de diagonais da matriz A.
    ω:  o pré-condicionador a ser utilizado:

        ω=-1: sem pré-condicionador
        ω=0.0 : pré-condicionador de Jacobi
        ω=1.0 pré-condicionador de Gauss-Seidel (opcional)
        1.0 < ω < 2.0: pré-condicionador SSOR (opcional)

    maxit:  o número máximo de iterações a serem executadas.
    ε: o erro aproximado absoluto máximo, considerando a norma maxima em x ( max ( |xi - xi-1| ) < ε ).
