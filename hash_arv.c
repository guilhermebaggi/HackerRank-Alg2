/*Implemente um TAD para hashing estático aberto, onde as colisões devem ser resolvidas por meio de árvores rubro-negras. A função hash deve ser o da multiplicação.

Input Format

Na primeira linha devem ser lidos a constante c considerada na alocação de chaves (tipo float), sendo que 0 < c < 1 e o tamanho n da tabela hash (tipo int). Na segunda linha deve ser lida a quantidade de chaves que serão alocadas. Por fim, devem ser lidas as chaves que serão alocadas na tabela hash.

Constraints

.
Output Format

Imprimir as posições onde as chaves foram colocadas na tabela. Em seguida, se a i-ésima posição da tabela for nula, ou seja, sem chave alocada, deve ser impresso "-". Caso contrário imprimir a árvore de forma pré-fixa.*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct NodeVP NodeVP;

struct NodeVP{
    int key;
    int color;
    NodeVP *father;
    NodeVP *left;
    NodeVP *right;
};

NodeVP *criar_AVP(int key){
    NodeVP *tree = (NodeVP *)malloc(sizeof(NodeVP));
    tree->key = key;
    tree->color = 0;
    tree->left = tree->right = tree->father = NULL;
    return tree;
}

NodeVP *rotacionar_esq(NodeVP *root, NodeVP *x){
    NodeVP *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->father = x;
    y->father = x->father;
    if (x->father == NULL)
        root = y;
    else if (x == x->father->left)
        x->father->left = y;
    else
        x->father->right = y;
    y->left = x;
    x->father = y;
    return root;
}

NodeVP *rotacionar_dir(NodeVP *root, NodeVP *x){
    NodeVP *y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->father = x;
    y->father = x->father;
    if (x->father == NULL)
        root = y;
    else if (x == x->father->right)
        x->father->right = y;
    else
        x->father->left = y;
    y->right = x;
    x->father = y;
    return root;
}

NodeVP *balancear_insercao(NodeVP *root, NodeVP *x){

    while (x != root && x->father->color == 0){
        if (x->father == x->father->father->left){
            NodeVP *y = x->father->father->right;
            if (y != NULL && y->color == 0){
                x->father->color = 1;
                y->color = 1;
                x->father->father->color = 0;
                x = x->father->father;
            }
            else{
                if (x == x->father->right)
                {
                    x = x->father;
                    root = rotacionar_esq(root, x);
                }
                x->father->color = 1;
                x->father->father->color = 0;
                root = rotacionar_dir(root, x->father->father);
            }
        }
        else{
            NodeVP *y = x->father->father->left;
            if (y != NULL && y->color == 0){
                x->father->color = 1;
                y->color = 1;
                x->father->father->color = 0;
                x = x->father->father;
            }
            else{
                if (x == x->father->left){
                    x = x->father;
                    root = rotacionar_dir(root, x);
                }
                x->father->color = 1;
                x->father->father->color = 0;
                root = rotacionar_esq(root, x->father->father);
            }
        }
    }
    root->color = 1;
    return root;
}

NodeVP *inserir_AVP(NodeVP *root, int key){
    NodeVP *novo = criar_AVP(key);
    NodeVP *y = NULL;
    NodeVP *x = root;

    while (x != NULL){
        y = x;
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    novo->father = y;
    if (y == NULL)
        root = novo;
    else if (key < y->key)
        y->left = novo;
    else
        y->right = novo;

    return balancear_insercao(root, novo);
}

void imprimir_AVP(NodeVP *tree){
    if (tree != NULL){
        printf("%d", tree->key);
        if (tree->left != NULL || tree->right != NULL){
            printf(" ");
        }
        imprimir_AVP(tree->left);
        if (tree->left != NULL && tree->right != NULL){
            printf(" ");
        }
        imprimir_AVP(tree->right);
    }
}

void imprimir(NodeVP *root){
    if (root == NULL){
        printf("-");
    }
    else{
        imprimir_AVP(root);
    }
    printf("\n");
}

typedef struct{
    int tam;
    NodeVP **buckets;
    float c;
} HashT;

HashT *criar(int tam, float c){
    HashT *t = (HashT *)malloc(sizeof(HashT));
    t->tam = tam;
    t->c = c;
    t->buckets = (NodeVP **)malloc(tam * sizeof(NodeVP *));
    for (int i = 0; i < tam; i++){
        t->buckets[i] = NULL;
    }
    return t;
}

int hashingF(int k, float c, int m){
    return (int)(m * fmod(k * c, 1.0));
}

int inserir(int key, HashT *t){
    int pos = hashingF(key, t->c, t->tam);
    t->buckets[pos] = inserir_AVP(t->buckets[pos], key);
    return pos;
}

int main(){

    float c;
    int n;
    int fim;
    int key;

    scanf("%f %d", &c, &n);
    HashT *t = criar(n, c);

    scanf("%d", &fim);
    for (int i = 0; i < fim; i++){
        scanf("%d", &key);
        inserir(key, t);
    }

    for (int i = 0; i < n; i++){
        printf("%d: ", i);
        imprimir(t->buckets[i]);
    }

    return 0;
}
