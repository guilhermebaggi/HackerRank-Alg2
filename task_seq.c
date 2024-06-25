/*Dada uma máquina que execute uma sequência de n Tarefas. Cada tarefa tem um tempo de execução e um deadline

. É desejável que todas as Tarefas sejam finalizadas sem atrasos, mas nem sempre isso é possível. Uma alternativa para compensar possíveis atrasos, seria a execução de Tarefas que terminam antes do tempo e aproveitar esse saldo para executar as outras Tarefas. No final da execução de todas as Tarefas, se o saldo de tempo (deadline - tempo de execução acumulado) for maior igual a zero, então o atraso é igual a zero. Caso o saldo de tempo seja negativo, então o atraso é equivalente ao módulo desse saldo (nesse problema, basta multiplicar o saldo por -1). Desse, o objetivo seria encontrar uma sequência de atividades que minimize o atraso.

Implemente uma função que receba um vetor de atividades de tamanho n. A função deverá imprimir a sequência ótima de atividades que foram executados até ou antes do deadline e retornar o valor do atraso.*/

#include <stdio.h>
#include <limits.h>

typedef struct{
  int id;
  int e;
  int d;
} Tarefas;

int maiorValor(int *v, int n){
  int i;
  int aux; 
  int ind = 0;

  aux = v[0];
  for (i = 0; i < n; i++){
    if (aux < v[i]){
      aux = v[i];
      ind = i;
    }
  }
  return ind;
}

void seqTasks(Tarefas *a, int n){
  int v[n];
  int pos[n];
  int i;

  for (i = 0; i < n; i++){
    v[i] = a[i].d - a[i].e;
  }

  for (i = 0; i < n; i++){
    pos[i] = maiorValor(v, n);
    v[pos[i]] = INT_MIN;
  }

  for (i = 0; i < n; i++){
    printf("%d ", pos[i]);
  }
  printf("\n");
}

int atraso(Tarefas *a, int n){
  int c = 0;
  int b = 0;

  for (int i = 0; i < n; i++){
    b += a[i].d;
    c += a[i].e;
  }

  return (b - c > 0) ? 0 : (b - c) * -1;
}

int main(){
  int n;
  scanf("%d", &n);

  Tarefas tarefa[n];
  for (int i = 0; i < n; i++){
    tarefa[i].id = i;
    scanf("%d %d", &tarefa[i].e, &tarefa[i].d);
  }

  seqTasks(tarefa, n);

  int res = atraso(tarefa, n);
  printf("%d\n", res);

  return 0;
}
