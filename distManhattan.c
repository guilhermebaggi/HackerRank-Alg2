/*Implemente, utilizando divisão e conquista, uma função para calcular a distância de Manhattan entre dois vetores de mesmo tamanho.

Equação da distância de Manhattan entre dois vetores: */

#include <stdio.h>

distManhattan(int a[], int b[], int in, int fi)
{
    int mei;
    int le;
    int ri;

    if (in == fi)
    {
        return abs(a[in]-b[fi]);
    }
    mei = (in + fi) / 2;
    le = distManhattan(a, b, in, mei);
    ri = distManhattan(a, b, mei + 1, fi);

    return le + ri;

}

int main(void)
{

    int n;
    int res;
    scanf("%d", &n);

    int vetA[n];
    int vetB[n];

    for (int i = 0; i < n; i++)
    {

        scanf("%d", &vetA[i]);
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &vetB[i]);
    }

    res = distManhattan(vetA, vetB, 0, n-1);
    printf("%d\n", res);

    return 0;
}