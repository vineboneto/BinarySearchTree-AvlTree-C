#ifndef AVL_H
#define AVL_H
#include "book.h"

/* Estrutura do Nodo */
typedef struct sNodo {
    struct sNodo *left;
    struct sNodo *right;
    int height;
    int key;
} Nodo ;

/* Cria um nodo */ 
Nodo* createNodo(int key);
/* Realiza a rotaçaõ a direita */
Nodo* rightRotate(Nodo* root);
/* Realiza a rotação a esquerda do nodo */
Nodo* leftRotate(Nodo* root);
/* Realiza a inserção do nodo na árvore AVL */
Nodo* insert(Nodo* root, int key);
/* Realiza a remoção do nodo na árovre AVL */
Nodo* _delete(Nodo* root, int key);
/* Aplica a remoção do elemento caso o nodo tenha apenas um ou nenhum filho */
Nodo* hasOneOrNoSon(Nodo* root);
/* Aplica a remoção do elemento caso o nodo tenha dois filhos */
Nodo* hasTwoSon(Nodo* root);
/* Pega o menor da valor da subárvore do nodo */
Nodo* minValueNodo(Nodo* root);
/* Realiza o balanceamento ao remover um elemento */
Nodo* balanceDelete(Nodo* root);
/* Realiza o balanceamento ao inserir um novo elemento */
Nodo* balanceInsert(Nodo* root, int key);

/* Retorna o fato de balanceamento do nodo em questão */
int getBalance(Nodo* root);
/* Retorna a altura do nodo em questão */
int height(Nodo* nodo);
/* Retorna o maior valor entre dois valores */
int max(int a, int b);
/* Imprimi a lista em Pre-Ordem */
void preOrder(Nodo* root);

#endif