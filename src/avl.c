#include <stdio.h>
#include <stdlib.h>
#include "headers/avl.h"

int main () {

    Nodo* root = NULL;


    return EXIT_SUCCESS;
}

Nodo* createNodo(int key) {
    Nodo* n = NULL;
    n = (Nodo*) malloc(sizeof(Nodo));
    if (!n) {
        perror("Overflow");
        exit(EXIT_FAILURE);
    }
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    return n;
}