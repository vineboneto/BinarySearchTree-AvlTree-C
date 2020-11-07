#include <stdio.h>
#include <stdlib.h>

typedef struct sNodo {
    struct sNodo *left;
    struct sNodo *right;
    int* data;
} Nodo;

Nodo* createNodo();
void insert(Nodo*, int*);
int delete (Nodo*, int*);
void cleanElement(Nodo*);
Nodo* search(Nodo*, int*);

Nodo* getMin(Nodo*);
Nodo* getOld(Nodo*, int*);

int main () {

    Nodo* root = createNodo();
    root->data = 5;

    insert(root, 10);
    insert(root, 15);
    insert(root, 16);
    insert(root, 12);
    insert(root, 11);
    insert(root, 7);
    insert(root, 8);
    insert(root, 6);
    insert(root, 11);
    insert(root, 3);
    insert(root, 4);
    insert(root, 2);
    insert(root, 1);

    int err;
    err = delete(root, 1);
    if (err == -1) {
        printf("Erro ao deletar elemento\n");
    } else {
        printf("Elemento deletado\n");
    }
    insert(root, 1);
    // insert(root, 10);

    printf("root->left %d\n", root->left->left->left->data);
    Nodo* aux = search(root, 1);
    if (!aux) {
        printf("Not Found!!\n");
    } else {
        printf("Found\n");
    }
    
    root = NULL;
    free(root);
    return 0;
}

Nodo* createNodo() {
    Nodo* nd = NULL;
    nd = (Nodo*) malloc(sizeof(Nodo));
    nd->left = NULL;
    nd->right = NULL;
    nd->data = malloc(sizeof(int));
    if (!nd) {
        exit(EXIT_FAILURE);
        perror("Overflow!!!");
    }
    return nd;
}

void insert(Nodo* root, int* data) {
    Nodo* nodo;
    if (data > root->data) {
        if (root->right) { 
            insert(root->right, data);
        } else {
            nodo = createNodo();
            nodo->data = data;
            root->right = nodo;
        }
    } else {
        if (root->left) {
            insert(root->left, data);
        } else {
            nodo = createNodo();
            nodo->data = data;
            root->left = nodo;
        }
    }
}

int delete(Nodo* root, int* data) {
    // Elemento existe ?
    Nodo* nodo = search(root,  data);
    if (!nodo) { 
        return -1;
    }    
    printf("Nodo: %d\n", nodo->data);
    // Captura o elemento anterior
    Nodo* oldNodo = getOld(root, data);
    // Primeiro caso não existem filhos
    if (!nodo->right && !nodo->left) {   
        if (oldNodo->right == nodo) oldNodo->right = NULL;
        else oldNodo->left = NULL;
    //Possui somente um filho a direita
    } else if (nodo->right && !nodo->left) {
        if (oldNodo->right == nodo) oldNodo->right == nodo->right;
        else oldNodo->left = nodo->right;
    // Possui somente um filho a esquerda
    } else if (nodo->left && !nodo->right) {
        if (oldNodo->right == nodo) oldNodo->right == nodo->left;
        else oldNodo->left = nodo->left;
    // Possui filhos a direita e a esquerda
    } else {
        // Pega o menor elemento a esquerda do elemento sendo removido
        Nodo* min = getMin(nodo->right);
        if (oldNodo->right == nodo) oldNodo->right = min;
        else oldNodo->left = min;
        min->left = nodo->left;
    }
    // Libera memória
    free(nodo);
    free(nodo->data);
    nodo = NULL;
    return 0;
}

// Pega Nodo anterior ao elemento anterior
Nodo* getOld(Nodo* root, int* data) {
    Nodo* aux;

    if (root->data < data) {
        if (root->right->data == data) {
            return root;
        } else {
            aux = getOld(root->right, data);
        }
    } else {
        if (root->left->data == data) {
            return root;
        } else {
            aux = getOld(root->left, data);
        }
    }
    
    return aux;
}

// Pegar o menor valor do ramo direitos
Nodo* getMin(Nodo* root) {
    Nodo* min;
    
    if (!root->left) {
        return root;
    } else {
        min = getMin(root->left);
    }
    return min;
}

Nodo* search(Nodo* root, int* data) {
    Nodo* nodo = NULL;
    if (root->data == data) {
        return root;
    } else if (data >= root->data) {
        if (root->right) nodo = search(root->right, data);
        else return NULL;
    } else {
        if (root->left) nodo = search(root->left, data);
        else return NULL;
    }

    return nodo;
}
