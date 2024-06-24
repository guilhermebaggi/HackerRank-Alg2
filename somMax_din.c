/*Seja um arranjo composto por números inteiros, podendo ser positivos e/ou negativos. A subsequência máxima é aquela que tem o maior valor de soma entre todos os os seus elementos.

Por exemplo, dada a sequência a seguir:

.

A subsequência máxima é

, pois, de todas as subsequências possíveis, essa foi a que registrou a maior soma entre os seus elementos (43).

Implemente, utilizando a estratégia programação dinâmica, uma função que retorne o somatório da subsequência máxima.*/

#include <stdio.h>
#include <limits.h>

int somMaxDin(int arr[], int n) {
    if (n == 0) {
        return 0;
    }

    int v[n];
    v[0] = arr[0];
    int max_sum = v[0];

    for (int q = 1; q < n; q++) {
        v[q] = arr[q];
        if (v[q-1] >= 0) {
            v[q] += v[q-1];
        }
        if (v[q] > max_sum) {
            max_sum = v[q];
        }
    }

    return max_sum;
}

int main() {
    int n;
    
    scanf("%d", &n);
    
    int arr[n];
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int res = somMaxDin(arr, n);
    printf("%d\n", res);

    return 0;
}
