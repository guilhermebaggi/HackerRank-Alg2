/*Seja um arranjo composto por números inteiros, podendo ser positivos e/ou negativos.
A subsequência máxima é aquela que tem o maior valor de soma entre todos os os seus elementos.
Implemente, utilizando a estratégia força-bruta, uma função que retorne o somatório da subsequência máxima.*/

#include <stdio.h>
#include <limits.h> // Para INT_MIN

int subMax(int q, int v[]){

    int max = INT_MIN;
    int i;
    int j;

    for (i = 0; i < q; i++){
        int aux = 0;
        for (j = i; j < (q-1) ; j++){
            aux += v[j];
            if (aux > max){
                max = aux;
            }
        }
    }
    return max;
}

int main(void){

    int quant;
    int i;

    // quantidade de elemento no arranjo
    scanf("%d", &quant);
    int v[quant];

    // elementos do arranjo
    for (i = 0; i < quant; i++){
        scanf("%d", &v[i]);
    }

    int sommax = subMax(quant, v);

    printf("%d\n", sommax);

    return 0;
}