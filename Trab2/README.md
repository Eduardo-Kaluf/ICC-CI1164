# EDUARDO KALUF - GRR 20241770

O trabalho foi feito utilizando o método de Gauss-Seidel adaptado para matrizes tridiagonais, 
pois é mais eficaz do que calcular a EDO durante a iteração. 
Isto foi verificado no exercício 2.

Casos em que a diagonal principal não é dominante não foram tratados, 
pois uma estratégia de pivoteamento deveria ser implementada. 
Porém, ela impede a utilização da abordagem tridiagonal, que é o foco do trabalho.

Além disso, em casos onde a diagonal principal possui zeros, podem ocorrer divisões por zero.
