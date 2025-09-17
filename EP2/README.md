# EDUARDO KALUF - GRR 20241770

O trabalho foi desenvolvido utilizando o método de Gauss-Seidel adaptado para matrizes tridiagonais, 
uma abordagem que se mostrou mais eficaz do que o cálculo da Equação Diferencial Ordinária (EDO) a cada 
iteração, conforme verificado no exercício 2.

Casos em que a diagonal principal não é dominante não foram abordados, 
pois exigiriam a implementação de uma estratégia de pivoteamento. Tal estratégia, no entanto, inviabilizaria o uso da 
abordagem tridiagonal, que constitui o foco deste trabalho. Adicionalmente, a presença de zeros na diagonal principal 
poderia levar a divisões por zero, uma condição não tratada.

No enunciado do exercício, a norma de parada especificada é de 10^−5. Contudo, com base no exemplo de execução 
fornecido, interpretou-se que o valor desejado seria 1^10−5. Adotando este último critério, foi possível alcançar a 
precisão requerida para a norma, na ordem de e−06.

-------

Para compilar com o likwid rode:

make lik-all

Para compilar sem o likwid:

make

-------

A fim de poder ter duas compilações diferentes o nome dos arquivos são respectivamente:

resolveEDO-likwid
resolveEDO

-------

Para rodar o script de testes com o likwid rode:

./teste.sh < teste.dat

