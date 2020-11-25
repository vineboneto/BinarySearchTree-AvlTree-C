#ifndef HEAP_H
#define HEAP_H
#include "book.h"

/* Estrutura do nodo */
typedef struct sNodo {
    struct sNodo *left;
    struct sNodo *right;
    Book* book;
} Nodo;

/* Cria um novo nodo */
Nodo* createNodo();
/* Insere um novo nodo na árvore */
Nodo* insert(Nodo* root, Book* book);
/* Remove um nodo da árvore */
Nodo* _delete (Nodo* root, Book* book);
/* Remove todos os elementos da árvore */
Nodo* deleteAll(Nodo* root);
/* Realiza a pesquisa de um determinado livro */
Nodo* search(Nodo* nodo, int issn);
/* Caso de remoção sem filhos */
Nodo* withoutSon(Nodo* root);
/* Caso de remoção que possui apenas um filho */
Nodo* hasOneSon(Nodo* root, Nodo* rootDirection);
/* Caso de remoção que possui dois filhos */
Nodo* hasTwoSon(Nodo* root, Book* book);
/* Libera memória do nodo */
void freeMemory(Nodo* nodo);
/* Imprime a árvore em ordem crescente */
void order(Nodo* root);
/* Imprime a árvore em Pre-Ordem */
void preOrder(Nodo* root);
/*  Imprime a árvore em Pós-Ordem */
void posOrder(Nodo* root);

#endif


