#ifndef AVL_H
#define AVL_H
#include "book.h"

typedef struct sNodo {
    struct sNodo *left;
    struct sNodo *right;
    int height;
    int key;
} Nodo ;

Nodo* createNodo(int key);
Nodo* rightRotate(Nodo* nodo);
Nodo* leftRotate(Nodo* nodo);
Nodo* insert(Nodo* nodo, int key);

int getBalance(Nodo* nodo);
int height(Nodo* nodo);
int max(int a, int b);
void preOrder(Nodo* root);

#endif