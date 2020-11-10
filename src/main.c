#include <stdio.h>
#include <stdlib.h>

typedef struct sBook {
    int issn;
    int year;
    char* name;
} Book;

typedef struct sNodo {
    struct sNodo *left;
    struct sNodo *right;
    Book* book;
} Nodo;



Nodo* createNodo();
Nodo* insert(Nodo*, int);
Nodo* delete (Nodo*, int);
Nodo* deleteAll(Nodo*);

Nodo* search(Nodo*, int);
void order(Nodo*);
void preOrder(Nodo*);
void posOrder(Nodo*);

int main () {

    Nodo* root = createNodo();
    root->data = 5;

    root = deleteAll(root);
    system("pause");
    return 0;
}

Nodo* createNodo() {
    Nodo* n = NULL;
    n = (Nodo*) malloc(sizeof(Nodo));
    n->left = n->right = NULL;
    n->book = createBook();
    if (!n) {
        exit(EXIT_FAILURE);
        perror("Overflow!!!");
    }
    return n;
}

Book* createBook() {
    Book* b = NULL;
    size_t bytes = 256;
    b = malloc(sizeof(Book));
    if (!b) {
        exit(EXIT_FAILURE);
        perror("Overflow!!");
    }
    b->name = malloc(bytes);
    return b;
}

Nodo* insert(Nodo* root, int data) {
    if (!root) {
        root = createNodo();
        root->data = data;
    } 
    else if (data < root->data) root->left = insert(root->left, data);
    else root->right = insert(root->right, data);

    return root;
}

Nodo* delete(Nodo* root, int data) {
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

Nodo* search(Nodo* root, int data) {
    if (!root) return NULL;
    else if (root->data > data) return search(root->left, data);
    else if (root->data < data) return search(root->right, data);
    else return root;
}

Nodo* deleteAll(Nodo* root) {
    if (root) {
        root->left = deleteAll(root->left);
        root->right = deleteAll(root->right);
        printf("Elemento deletado %d\n", root->data);
        free(root);
    }
    return NULL;
}

void order(Nodo* nodo) {
    if (nodo) {
        order(nodo->left);
        printf("%d \n", nodo->data);
        order(nodo->right);
    }
}

void preOrder(Nodo* nodo) {
    if (nodo) {
        printf("%d \n", nodo->data);
        preOrder(nodo->left);
        preOrder(nodo->right);
    }
}

void posOrder(Nodo* nodo) {
    if (nodo) {
        posOrder(nodo->left);
        posOrder(nodo->right);
        printf("%d \n", nodo->data);
    }
}