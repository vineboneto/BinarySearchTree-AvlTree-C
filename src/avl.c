#include <stdio.h>
#include <stdlib.h>
#include "headers/avl.h"

int main () {

    Nodo* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    /* The constructed AVL Tree would be 
            30 
           /  \ 
         20   40 
        /  \     \ 
       10  25    50 
    */
    printf("root: %d\n", root->key);
    printf("root->right: %d\n", root->right->key);
    printf("root->left: %d\n", root->left->key);
    
    preOrder(root);


    return EXIT_SUCCESS;
}

Nodo* createNodo(int key) {
    Nodo* n = NULL;
    n = (Nodo*) malloc(sizeof(Nodo));
    if (!n) {
        perror("Overflow");
        exit(EXIT_FAILURE);
    }
    n->left = n->right = NULL;
    n->height = 1;
    n->key = key;
    return n;
}

Nodo* insert(Nodo* root, int key) {
    // Primeiro elemento
    if (!root) return createNodo(key);

    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    else return root;

    // printf("Cheogu aqui\n");
    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root);

    // Caso Left Left
    if (balance > 1 && key < root->left->key) return rightRotate(root);

    //Caso Right Right
    if (balance < -1 && key > root->right->key) return leftRotate(root);

    // Caso Left Right
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Caso Right Left
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);    
    }

    return root;
}

Nodo* rightRotate(Nodo* nodoY) {
    Nodo* nodoX = nodoY->left;
    Nodo* nodoT2 = nodoX->right;

    // Rotação
    nodoX->right = nodoY;
    nodoY->left = nodoT2; 

    // Atualizção de heights
    nodoY->height = max(height(nodoY->left), height(nodoY->right)) + 1;
    nodoX->height = max(height(nodoX->left), height(nodoX->right)) + 1;
    
    // Retorna o novo root
    return nodoX;
}

Nodo* leftRotate(Nodo* nodoX) {
    Nodo* nodoY = nodoX->right;
    Nodo* nodoT2 = nodoY->left;

    // Rotação
    nodoY->left = nodoX;
    nodoX->right = nodoT2;

    // Atualizção de heights
    nodoX->height = max(height(nodoX->left), height(nodoX->right)) + 1;
    nodoY->height = max(height(nodoY->left), height(nodoY->right)) + 1;

    // Retorna o novo root
    return nodoY;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int height(Nodo* nodo) {
    if (!nodo) return 0;
    return nodo->height;
}

int getBalance(Nodo* root) {
    if (!root) return 0;
    return height(root->left) - height(root->right);
}

void preOrder(Nodo* root) {
    if (root) {
        printf("%d ", root->key); 
        preOrder(root->left); 
        preOrder(root->right); 
    }
}