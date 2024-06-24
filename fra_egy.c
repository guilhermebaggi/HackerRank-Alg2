/*Uma fração pode representada pela soma de um conjunto de frações unitárias, onde o numerador é igual a 1 (um). Exemplos:

    8/11 é equivamente a 1/2 + 1/5 + 1/37 + 1/4070.

    7/3 é equivamente a 2 + 1/3.

Essas frações unitárias podem ser geradas utilizando uma estratégia gulosa. Dado dois números inteiros: n (numerador) e d (demoninador).

Se d > n, o denominador da maior fração unitária é dada da seguinte forma: 1 / (d / n). Após, pode ser feita uma chamada recursiva, cuja fração de entrada deve ser equivalente a (n / d) - (1 / (d / n + 1)), que é igual a uma outra fração: (n * (d / n + 1) - d) / (d * (d / n + 1)). Por exemplo, para o 8/11, a primeira fração unitária é 1 / (d / n + 1) = 1 / (11 / 8 + 1) = 1/2. Em seguida, pode ser feita uma chamada recursiva para 8/11 - 1/2 = 5/22, ou seja, (8 * (11/8 + 1) - 11) / ((11/8 + 1) * 11) = 5/22.

Se d < n, o resultado é um número inteiro mais uma fração resultante da chamada recursiva para seguinte fração: (n % d) / d. Por exemplo, para 7/3, o numerador é maior, ou seja, primeiro deverá ser impresso a parte inteira da divisão (2). Em seguinda, fazer uma chamada recursiva para (n % d) / n = (7 % 3) / 3 = 1/3.

Os critérios de parada são:

    d % n == 0

    n % d == 0

Implemente uma função que receba, pelo menos, dois números inteiros que represente uma fração. A função deverá imprimir o somatório de frações unitárias e/ou números inteiros cujo resultado é a fração de entrada.*/

#include <stdio.h>
#include <string.h>

void dec_fra_egy(int num, int den, char *fra) {
  if (den % num == 0) {
    sprintf(fra, "1/%d", den / num);
  } else if (num >= den) {
    int p_inte = num / den;
    int resto = num % den;
    sprintf(fra, "%d + ", p_inte);
    dec_fra_egy(resto, den, fra + strlen(fra));
  } else {
    int fra_unit = den / num + 1;
    int nv_num = num * fra_unit - den;
    int nv_den = den * fra_unit;
    sprintf(fra, "1/%d + ", fra_unit);
    dec_fra_egy(nv_num, nv_den, fra + strlen(fra));
  }
}

int main() {
  int num, den;

  scanf("%d %d", &num, &den);

  char fra[100];
  dec_fra_egy(num, den, fra);

  printf("%s\n", fra);

  return 0;
}