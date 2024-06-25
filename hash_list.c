/*Implemente um TAD para hashing estático aberto, onde as colisões devem ser resolvidas por meio de listas encadeadas ordenadas. A função hash deve ser resto de divisão, ou seja, h(k) = k % B, onde k é uma chave e B é o tamanho da tabela hash.

Input Format

Na primeira linha deve ser lido o tamanho da tabela hash. Na segunda linha deve ser lida a quantidade de chaves que serão alocadas. Por fim, devem ser lidas as chaves que serão alocadas na tabela hash.

Constraints

.

Output Format

Imprimir as posições onde as chaves foram colocadas na tabela. Em seguida, imprimir a tabela hash inteira. Para isso, deve ser considerado o seguinte formato: "linha_i: -> item_0 -> item_1 -> ... -> item_n"

Caso a i-ésima linha da matriz esparsa seja nula, basta imprimir "linha_i -> ".*/


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct Cell Cell;

typedef struct ListaE ListaE;

struct Cell{
    int item;
    
    Cell *next;
};



struct ListaE{
    Cell *head;
};


Cell* criar_celula(int key){
    Cell *c = (Cell*) malloc(sizeof(Cell));
    c->item = key;

    c->next = NULL;

    return c;
}

ListaE* criar_listaE(){
    ListaE* l = (ListaE*) malloc(sizeof(ListaE));

    l->head = NULL;

    return l;
}


int listaE_vazia(ListaE *l){
    return (l == NULL) || (l->head == NULL);
}


void inserir_primeiro(int key, ListaE *l){
    Cell *aux;

    if (l == NULL)
        l = criar_listaE();

    aux = criar_celula(key);

    aux->next = l->head;

    l->head = aux;
}

void imprimir_lista(ListaE *l){
    Cell *aux;
    
    if (!listaE_vazia(l)){
        aux = l->head;

        while (aux != NULL){
            printf(" -> %d", aux->item);

            aux = aux->next;
        }

        printf("\n");
    }else
        printf(" ->\n");
}

void inserir_ordenado(int key, ListaE *l){
    Cell *auxA, *auxP, *nova;

    if (l == NULL)
        l = criar_listaE();

    if (listaE_vazia(l))
        inserir_primeiro(key, l);
    else{
        nova = criar_celula(key);

        if ((l->head == NULL) || (l->head->item <= key)){
            nova->next = l->head;
            l->head = nova;
        }else{
            auxP = auxA = l->head;

            while((auxA != NULL) && (key > auxA->item)){
                auxP = auxA;

                auxA = auxA->next;
            }

            auxP->next = nova;
 
            nova->next = auxA;
        }
    }
}

typedef struct{
    unsigned int tam;
    ListaE **buckets;
}HashT;


HashT *criar(unsigned int tam){
    HashT *t = malloc(sizeof(HashT));
    int i;

    t->tam = tam;
    t->buckets = (ListaE**) malloc(tam * sizeof(ListaE*));

    for (i = 0; i < tam; i++)
        t->buckets[i] = criar_listaE();

    return t;
}


static int hashingF(int k, int B){
    return k % B;
}


static int overflow_prog(int hashC, int B, int tentativa){
    return (hashC + tentativa) % B;
}


int inserir(int key, HashT *t){
    int x;
    int i, rh;

    if ((t != NULL) && (key > 0)){
        x = hashingF(key, t->tam);
        inserir_ordenado(key, t->buckets[x]);
        return x;
    }

    return 0;
}

void imprimir(HashT *t){
    int i;
    if (t != NULL){
        for (i = 0; i < t->tam; i++){
            printf("%d:", i);
            
            imprimir_lista(t->buckets[i]);
        }
    }
}


int main(void){
    
    int n, end, key, i;
    
    scanf("%d", &n);
    scanf("%d", &end);
    
    HashT *t = criar(n);
    
    for(i = 0; i < end; i++){
        scanf("%d", &key);
        int pos = inserir(key, t);
        printf("%d",pos);
    }

    printf("\n");
    
    imprimir(t);
    
    return 0;
}
