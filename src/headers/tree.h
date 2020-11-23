#ifndef HEAP_H
#define HEAP_H
#include "book.h"

typedef struct sNodo {
    struct sNodo *left;
    struct sNodo *right;
    Book* book;
} Nodo;

Nodo* createNodo();
Nodo* insert(Nodo* root, Book* book);
Nodo* delete (Nodo* root, Book* book);
Nodo* deleteAll(Nodo* root);
Nodo* search(Nodo* nodo, int issn);
Nodo* withoutSon(Nodo* root);
Nodo* hasOneSon(Nodo* root, Nodo* rootDirection);
Nodo* hasTwoSon(Nodo* root, Book* book);

void freeMemory(Nodo* nodo);
void order(Nodo* root);
void preOrder(Nodo* root);
void posOrder(Nodo* root);

#endif


