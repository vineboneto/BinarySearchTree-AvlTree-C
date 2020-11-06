#include <stdio.h>
#include <stdlib.h>

typedef struct sNodo {
    struct sNodo *left;
    struct sNodo *right;
    int data;
} Nodo;

Nodo* createNodo();
void insert(Nodo*, int);
int delete (Nodo*, int);
Nodo* search(Nodo*, int);

int getMin(Nodo*);

int main () {

    Nodo* root = createNodo();
    root->data = 5;


    insert(root, 2);
    insert(root, 12);
    insert(root, 7);
    insert(root, 6);
    insert(root, 3);
    insert(root, 4);
    insert(root, 1);

    Nodo* no = search(root, 6);
    if (!no) {
        printf("Not found!\n");
    } else {
        printf("Searched element: %d\n", no->data);
    }

    // free(no);
    // delete(root, 2);

    // Nodo* res = search(root, 2);
    // if (res) {
    //     printf("Found number: %d\n", res->data);
    // } else {
    //     printf("Not Found Number");
    // }


    root = NULL;
    free(root);
    return 0;
}

Nodo* createNodo() {
    Nodo* nd = NULL;
    nd = (Nodo*) malloc(sizeof(Nodo));
    nd->left = NULL;
    nd->right = NULL;
    if (!nd) {
        exit(EXIT_FAILURE);
        perror("Overflow!!!");
    }
    return nd;
}

void insert(Nodo* root, int data) {
    Nodo* nodo;


    // if (!root) {
    //     root = createNodo();
    //     root->data = data;
    
    // } else {
    //     if (data > root->right) insert(root->right, data);

    //     if (data < root->left) insert(root->left, data);
    // }

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

int delete(Nodo* root, int data) {

    Nodo* aux;
    Nodo* nodo = search(root, data);
    if (nodo == NULL) { // Elemento existe ?
        return -1;
    }

    // Primeiro caso não possui filhos
    // aux = nodo;
    // if (nodo->right && !nodo->left) {          //Possui somente um filho
    //     // nodo->right->left = nodo->left;                       
    // } else if (nodo->left && !nodo->right) {   //Possui somente um filho
    //     nodo = nodo->left;
    // } else if (nodo->right && nodo->left) {    //Possui os dois filhos
    //     Nodo* min = getMin(nodo->right);
    //     nodo = min;
    // }

    printf("Number %d deleted\n", nodo->data);
    nodo = NULL;
    free(nodo);
    return 1;
}

// Pegar o menor valor do ramo direitos
int getMin(Nodo* root) {
    int min;
    
    if (!root->left) {
        min = root->data;
    } else {
        min = getMin(root->left);
    }
    return min;
}

Nodo* search(Nodo* root, int data) {
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
