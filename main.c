#include <stdio.h>
#include <stdlib.h>

typedef struct sNodo {
    struct sNodo *left;
    struct sNodo *right;
    int* data;
} Nodo;

Nodo* createNodo();
Nodo* insert(Nodo*, int*);
// Métodos utilizados para remoção
void delete (Nodo*, int*);
Nodo* getMin(Nodo*);
Nodo* getOld(Nodo*, int*);

Nodo* search(Nodo*, int*);


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


    Nodo* aux = search(root, 6);
    aux == NULL ? printf("Não encontarado") : printf("Elemento encontrado %d!\n", aux->data);
    
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
// // Pega Nodo anterior ao elemento anterior
// void delete(Nodo* root, int* data) {
//     if (root->data <= data) {
//         if (root->right->data == data) {
//             return root;
//         } else {
//             delete(root->right, data);
//         }
//     } else {
//         if (root->left->data == data) {
//             // O elemento possui filhos a equerda mas não a direita
//             if (root->left->left && !root->left->right) {
//                 root->left = root->left->left;
//             // O elemento possui filhos a direita mas não a esquerda
//             } else if (root->left->right && !root->left->left) {
//                 root->left = root->left->right;
//             } else {
//                 Nodo* min = getMin(root->left->right);
//                 min->left = root->left->left;
//                 root->left = min;
//                 printf("root->left: %d\n", root->left->data);
//                 printf("min->left: %d\n", min->left->data);
//                 printf("min->right: %d\n", min->right);
//             }

//             free(root->left);
//         }
//     }
// }


// // Pegar o menor valor do ramo direitos
// Nodo* getMin(Nodo* root) {
//     Nodo* min;
    
//     if (!root->left) {
//         return root;
//     } else {
//         min = getMin(root->left);
//     }
//     return min;
// }

Nodo* search(Nodo* root, int* data) {
    if (root == NULL) return NULL;
    else if (root->data > data) return search(root->left, data);
    else if (root->data < data) return search(root->right, data);
    else return root;
}
