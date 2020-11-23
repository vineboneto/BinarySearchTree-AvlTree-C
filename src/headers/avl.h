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
Nodo* rightRotate(Nodo* root);
Nodo* leftRotate(Nodo* root);
Nodo* insert(Nodo* root, int key);
Nodo* _delete(Nodo* root, int key);
Nodo* minValueNodo(Nodo* root);

int getBalance(Nodo* root);
int height(Nodo* nodo);
int max(int a, int b);
void preOrder(Nodo* root);

#endif