#include <stdio.h>
#include <stdlib.h>
#include "../headers/binary-search.h"

#include "book.c"

Nodo* createNodo(Book* book) {
    Nodo* n = NULL;
    n = (Nodo*) malloc(sizeof(Nodo));
    if (!n) {
        exit(EXIT_FAILURE);
        perror("Overflow!!!");
    }
    n->left = n->right = NULL;
    n->book = book;
    return n;
}

Nodo* insert(Nodo* root, Book* book) {
    if (!root) return createNodo(book);
    else if (book->issn < root->book->issn) root->left = insert(root->left, book);
    else root->right = insert(root->right, book);

    return root;
}

Nodo* _delete(Nodo* root, Book* book) {
    if (!root) return NULL;
    else if (root->book->issn > book->issn) root->left = _delete(root->left, book);
    else if (root->book->issn < book->issn) root->right = _delete(root->right, book);
    else {
        // Sem Filhos
        if (!root->left && !root->right) root = withoutSon(root);
        // So filhos a direita
        else if (!root->left) root = hasOneSon(root, root->right);
        // So tem filhos a esquerda 
        else if (!root->right) root = hasOneSon(root, root->left);
        // Tem os dois filhos
        else root = hasTwoSon(root, book);
        
    }
    return root;
}

Nodo* withoutSon(Nodo* root) {
    freeMemory(root);
    return NULL;
}

Nodo* hasOneSon(Nodo* root, Nodo* rootDirection) {
    Nodo* aux = root;
    root = rootDirection;
    freeMemory(aux);
    return root;
}

Nodo* hasTwoSon(Nodo* root, Book* book) {
    Nodo* aux = root->right;
    while (aux->left != NULL) {
        aux = aux->left;
    }
    root->book = aux->book; // Troca dados
    aux->book = book; // Troca dados
    root->right = _delete(root->right, book);
    return root;
} 

void freeMemory(Nodo* nodo) {
    free(nodo);
    free(nodo->book);
    free(nodo->book->name);
}

Nodo* search(Nodo* root, int issn) {
    if (!root) return NULL;
    else if (root->book->issn > issn) return search(root->left, issn);
    else if (root->book->issn < issn) return search(root->right, issn);
    else return root;
}

Nodo* deleteAll(Nodo* root) {
    if (root) {
        root->left = deleteAll(root->left);
        root->right = deleteAll(root->right);
        printf("Elemento deletado %d\n", root->book->issn);
        freeMemory(root);
    }
    return NULL;
}

void order(Nodo* nodo) {
    if (nodo) {
        order(nodo->left);
        displayBook(nodo->book);
        order(nodo->right);
    }
}

void preOrder(Nodo* nodo) {
    if (nodo) {
        displayBook(nodo->book);
        preOrder(nodo->left);
        preOrder(nodo->right);
    }
}

void posOrder(Nodo* nodo) {
    if (nodo) {
        posOrder(nodo->left);
        posOrder(nodo->right);
        displayBook(nodo->book);
    }
}