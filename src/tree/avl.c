#include <stdio.h>
#include <stdlib.h>
#include "../headers/avl.h"

#include "book.c"

Nodo* createNodo(Book* book) {
    Nodo* n = NULL;
    n = (Nodo*) malloc(sizeof(Nodo));
    if (!n) {
        perror("Overflow");
        exit(EXIT_FAILURE);
    }
    n->left = n->right = NULL;
    n->height = 1;
    n->book = book;
    return n;
}

Nodo* insert(Nodo* root, Book* book) {
    // Primeiro elemento
    if (!root) return createNodo(book);

    else if (book->issn < root->book->issn) root->left = insert(root->left, book);
    else if (book->issn > root->book->issn) root->right = insert(root->right, book);
    else return root;

    root->height = max(height(root->left), height(root->right)) + 1;
    // Realiza o balanceamento da árvore
    root = balanceInsert(root, book);

    return root;
}

Nodo* balanceInsert(Nodo* root, Book* book) {
    // Calcula o fator de balanceamento
    int balance = getBalance(root);
    // Caso LL
    if (balance > 1 && book->issn < root->left->book->issn) return rightRotate(root);
    //Caso RR
    if (balance < -1 && book->issn > root->right->book->issn) return leftRotate(root);

    // Caso LR
    if (balance > 1 && book->issn > root->left->book->issn) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Caso RL
    if (balance < -1 && book->issn < root->right->book->issn) {
        root->right = rightRotate(root->right);
        return leftRotate(root);    
    }

    return root;
}

Nodo* _delete(Nodo* root, Book* book) {
    if (!root) return NULL;
    else if (book->issn < root->book->issn) root->left = _delete(root->left, book);
    else if (book->issn > root->book->issn) root->right = _delete(root->right, book);
    else {
        // Sem filhos ou com somente um filho
        if (!root->left || !root->right) root = hasOneOrNoSon(root);
        // Possui dois filhos
        else root = hasTwoSon(root, book);
    }
    // Se a arvore possui apenas um filho
    if (!root) return root; 
   // Calcular altura do no root
    root->height = max(height(root->left), height(root->right)) + 1; 
    // Realiza o balanceamento
    root = balanceDelete(root);

    return root;
}

Nodo* hasOneOrNoSon(Nodo* root) {
    // Seleciona o filho que estiver com algum valor, caso nenhum tenha seleciona nulo
    Nodo* temp = root->left ? root->left : root->right;
    // Sem filhos
    if (!temp) {
        temp = root;
        root = NULL;
    } else *root = *temp; // Copia os dados para o root
    freeMemory(temp);
    return root;
}

Nodo* hasTwoSon(Nodo* root, Book* book) {
    // Captura o menor elemento a direita do root
    Nodo* temp = minValueNodo(root->right);
    // Troca de dados
    root->book = temp->book;
    temp->book = book;
    // Deleta o elemento troca
    root->right = _delete(root->right, book);
    return root;
}

Nodo* balanceDelete(Nodo* root) {
    int balance = getBalance(root); 
    // Caso LL
    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root); 
    // Caso RR
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);  
    // Caso LR
    if (balance > 1 && getBalance(root->left) < 0) { 
        root->left =  leftRotate(root->left); 
        return rightRotate(root); 
    } 
    // Caso RL
    if (balance < -1 && getBalance(root->right) > 0) { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    }

    return root;
}


// Realiza a  rotação a esquerda
Nodo* leftRotate(Nodo* nodoX) {
    // Auxliares
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

// Realiza a  rotação a direita
Nodo* rightRotate(Nodo* nodoY) {
    // Auxliares
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

Nodo* minValueNodo(Nodo* nodo) {
    Nodo* current = nodo;

    while (current->left != NULL) {
        current = current->left;
    }
    return current;
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

void preOrder(Nodo* root) {
    if (root) {
        displayBook(root->book);
        preOrder(root->left); 
        preOrder(root->right); 
    }
}

void posOrder(Nodo* nodo) {
    if (nodo) {
        posOrder(nodo->left);
        posOrder(nodo->right);
        displayBook(nodo->book);
    }
}

void freeMemory(Nodo* nodo) {
    free(nodo);
    free(nodo->book);
    free(nodo->book->name);
}

