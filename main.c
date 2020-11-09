#include <stdio.h>
#include <stdlib.h>

typedef struct sNodo {
    struct sNodo *left;
    struct sNodo *right;
    int* data;
} Nodo;

Nodo* createNodo();
Nodo* insert(Nodo*, int*);
Nodo* delete (Nodo*, int*);
Nodo* search(Nodo*, int*);
void show(Nodo*);


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
    insert(root, 3);
    insert(root, 4);
    insert(root, 2);
    insert(root, 1);


    show(root);

    // aux = search(root, 3);
    // aux == NULL ? printf("Nao encontarado\n") : printf("Elemento encontrado %d!\n", aux->data);
    
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

Nodo* insert(Nodo* root, int* data) {
    if (!root) {
        root = createNodo();
        root->data = data;
    } 
    else if (data < root->data) root->left = insert(root->left, data);
    else root->right = insert(root->right, data);

    return root;
}

Nodo* delete(Nodo* root, int* data) {
    if (!root) return NULL;
    else if (root->data > data) root->left = delete(root->left, data);
    else if (root->data < data) root->right = delete(root->right, data);
    else {
        // Sem Filhos
        if (!root->left && !root->right) {
            free(root);
            root = NULL;
        }
        // So filhos a direita
        else if (!root->left) {
            Nodo* aux = root;
            root = root->right;
            free(aux);
        }
        // So tem filhos a esquerda 
        else if (!root->right) {
            Nodo* aux = root;
            root = root->left;
            free(aux);
        }
        // Tem os dois filhos
        else {
            Nodo* aux = root->right;
            while (aux->left != NULL) {
                aux = aux->left;
            }
            root->data = aux->data; // troca informações
            aux->data = data;
            root->right = delete(root->right, data);
        }
    } 
    return root;
}

Nodo* search(Nodo* root, int* data) {
    if (root == NULL) return NULL;
    else if (root->data > data) return search(root->left, data);
    else if (root->data < data) return search(root->right, data);
    else return root;
}

void show(Nodo* root) {
    if (root) {
        show(root->left);
        printf(" %d\n", root->data);
        show(root->right);
    }
}
