/*Dada uma máquina que execute uma sequência de n tarefas. Cada tarefa tem um tempo de execução e um deadline

. É desejável que todas as tarefas sejam finalizadas sem atrasos, mas nem sempre isso é possível. Uma alternativa para compensar possíveis atrasos, seria a execução de tarefas que terminam antes do tempo e aproveitar esse saldo para executar as outras tarefas. No final da execução de todas as tarefas, se o saldo de tempo (deadline - tempo de execução acumulado) for maior igual a zero, então o atraso é igual a zero. Caso o saldo de tempo seja negativo, então o atraso é equivalente ao módulo desse saldo (nesse problema, basta multiplicar o saldo por -1). Desse, o objetivo seria encontrar uma sequência de atividades que minimize o atraso.

Implemente uma função que receba um vetor de atividades de tamanho n. A função deverá imprimir a sequência ótima de atividades que foram executados até ou antes do deadline e retornar o valor do atraso.*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Task {
  int id;
  int e;
  int d;
} Task;

int compare(const void *a, const void *b) {
  Task *taskA = (Task *)a;
  Task *taskB = (Task *)b;
  return taskA->d - taskB->d;
}

int seqtaskGuloso(Task tasks[], int n, int order[]) {
  qsort(tasks, n, sizeof(Task), compare);

  int currentTime = 0;
  int totalDelay = 0;
  int orderIndex = 0; 
  for (int i = 0; i < n; i++) {
    if (currentTime + tasks[i].e <= tasks[i].d) {
      order[orderIndex++] = tasks[i].id;
      currentTime += tasks[i].e;
    }
    if (currentTime > tasks[i].d) {
      totalDelay += currentTime - tasks[i].d;
    }
  }


  return totalDelay;
}

int main(void) {
  int n;
  scanf("%d", &n);

  Task tasks[n];
  int order[n];

  for (int i = 0; i < n; i++) {
    tasks[i].id = i + 1;
    scanf("%d %d", &tasks[i].e, &tasks[i].d);
  }

  int delay = seqtaskGuloso(tasks, n, order);

  for (int i = 0; i < n; i++) {
    printf("%d ", order[i]);
  }
  printf("\n");

  printf("%d\n", delay);

  return 0;
}