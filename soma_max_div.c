/*Dado um vetor de inteiros. Implemente uma função, utilizando divisão e conquista, que encontre a soma máxima no vetor. Por exemplo: para o vetor v = {-1, 3, 0, -2, 1, 3, -4, 5}, a soma máxima é 12 (3 + 0 + 1 + 3 + 5).

Input Format

A primeira linha deve ser um número inteiro n referente ao tamanho do vetor. Em seguinda, Para cada uma das próximas n linhas devem ser lidos os elementos do vetor.

Constraints

*/
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int somMaxDivConq(int vet[], int i, int f) {
    int x;
    if (i > f) 
        return 0;

    if (i == f){
        if (vet[i] < 0)
            return 0;
        else
            return vet[i];
    }

    x = (i + f) / 2;
    
    return somMaxDivConq(vet, i, x) + somMaxDivConq(vet, x + 1, f);
}

int main(){
    int n;
    int *vet;

    scanf("%d", &n);

    vet = malloc(sizeof(int) * n);
    
    for (int i = 0; i < n; i++)
        scanf("%d", &vet[i]);
   
    printf("%d\n", somMaxDivConq(vet, 0, n-1));
    
    free(vet);
    return 0;
}