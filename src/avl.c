#include <stdio.h>
#include <stdlib.h>
#include "headers/avl.h"

int main () {

    Nodo* root = NULL;
  /* Constructing tree given in the above figure */
    root = insert(root, 9); 
    root = insert(root, 5); 
    root = insert(root, 10); 
    root = insert(root, 0); 
    root = insert(root, 6); 
    root = insert(root, 11); 
    root = insert(root, -1); 
    root = insert(root, 1); 
    root = insert(root, 2); 
  
    /* The constructed AVL Tree would be 
            9 
           /  \ 
          1    10 
        /  \     \ 
       0    5     11 
      /    /  \ 
     -1   2    6 
    */
  
    printf("Preorder traversal of the constructed AVL "
           "tree is \n"); 
    preOrder(root); 
  
    root = _delete(root, 10); 
  
    /* The AVL Tree after deletion of 10 
            1 
           /  \ 
          0    9 
        /     /  \ 
       -1    5     11 
           /  \ 
          2    6 
    */
  
    printf("\nPreorder traversal after deletion of 10 \n"); 
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

Nodo* _delete(Nodo* root, int key) {
    if (!root) return NULL;
    else if (key < root->key) root->left = _delete(root->left, key);
    else if (key > root->key) root->right = _delete(root->right, key);
    else {
        // Sem filhos ou com somente um filho
        if (!root->left || !root->right) {
            Nodo* temp = root->left ? root->left : root->right;

            // Sem filhos
            if (!temp) {
                temp = root;
                root = NULL;
            } else *root = *temp;

            free(temp);
        // Possui dois filhos
        } else {
            Nodo* temp = minValueNodo(root->right);
            root->key = temp->key;
            root->right = _delete(root->right, temp->key);
        }
    }

    // Se a arvore possui apenas um filho
    if (!root) return root; 
   
    root->height = max(height(root->left), height(root->right)) + 1; 
  
    int balance = getBalance(root); 

    // Caso Left Left
    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root); 

    // Caso Right Right 
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root); 
  
    // Caso Left Right
    if (balance > 1 && getBalance(root->left) < 0) { 
        root->left =  leftRotate(root->left); 
        return rightRotate(root); 
    } 
  
    // Caso Right Left
    if (balance < -1 && getBalance(root->right) > 0) { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 
    return root;
}

Nodo* minValueNodo(Nodo* nodo) {
    Nodo* current = nodo;
    while (nodo->left != NULL) {
        current = current->left;
    }
    return current;
}