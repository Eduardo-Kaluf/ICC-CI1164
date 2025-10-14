# AUTORIA

- EDUARDO KALUF GRR20241770

- SERGIO SIVONEI DE SANT'ANA FILHO GRR20242337

# MÓDULOS

- _cgSolver.c_

    Módulo principal do programa, é nele que ocorre a leitura e a saída de dados, os cálculos e a temporização.  

- _gradiente_conjugado.c_

    Este módulo implementa o cálculo do gradiente conjugado e o cálculo da norma do sistema.

- _sislin.c_

    Este módulo implementa funções que modificam o sistema linear a fim de que o cálculo do gradiente conjugado possa ser realizado.

- _utils.c_

    Este módulo contém funções auxiliares que facilitam a leitura de dados, alocações e operações que são genéricas a fim de deixar o código mais limpo e legível

- _matriz.c_

    Este módulo implementa funções que realizam operações sobre matrizes

- _vetor.c_

    Este módulo implementa funções que realizam operações sobre vetores


# OTIMIZAÇÕES E ERROS

- A nossa função de gerar a matriz pré-condicionadora já retorna a sua inversa, evitando cálculos e acessos adicionais à memória.

- As operações sobre matrizes são (em geral) feitas levando em consideração que estamos trabalhando com uma matriz k-diagonal, evitando operações e acessos desnecessários à memória para zeros.

- O programa trata erros como má alocação de memória e geração de uma matriz que não possui inversa, além de outros erros comuns. No caso de um erro fatal, o programa será encerrado.

# I/O

A entrada do programa deve seguir as seguintes regras:

    n: Dimensão do Sistema Linear. (n > 10)
    k: O número de diagonais da matriz A. (k > 1 e k ímpar)  
    ω: O pré-condicionador a ser utilizado:

        ω = -1: sem pré-condicionador
        ω = 0.0: pré-condicionador de Jacobi
        ω = 1.0: pré-condicionador de Gauss-Seidel
        1.0 < ω < 2.0: pré-condicionador SSOR

    maxit: O número máximo de iterações a serem executadas.
    ε: O erro aproximado absoluto máximo, considerando a norma máxima em x ( max ( |xi - xi-1| ) < ε ).


A saída do programa segue o seguinte formato:

    Norma: Norma máxima do erro aproximado em x após a última iteração (||x||∞ = max|xi - xi-1|);
    Resíduo: A norma euclidiana do resíduo (||r||L2), onde r= b - Ax
    Tempo PC: Tempo para calcular a matriz pré-condicionante M e preparar o SL para o uso do pré-condicionante. (ms)
    Tempo iter: Tempo médio para calcular uma iteração do método, inclusive o cálculo do erro. (ms)
    Tempo residuo: Tempo para calcular a norma euclidiana do resíduo ao final do processo. (ms)
