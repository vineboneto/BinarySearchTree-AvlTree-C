#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int handleMenu();
Nodo* handleInsert(Nodo*);
Nodo* handleDelete(Nodo*);
Nodo* handleSelect(Nodo*, int);
void handleSearch(Nodo*);

int main () {
    system("cls");
    Nodo* root = NULL;

    int opc = 0;
    while (opc != 7) {
        opc = handleMenu();
        root = handleSelect(root, opc);
        system("pause");
        system("cls");
    }
    // Remove todos os elementos da árvore
    root = deleteAll(root);
    return 0;
}

int handleMenu() {
    int opc;
    printf("1 -> Inserir livro\n");
    printf("2 -> Deletar livro\n");
    printf("3 -> Pesquisar livro por ISSN\n");
    printf("4 -> Exibir livros em ordem\n");
    printf("5 -> Exibir livros em pre-ordem\n");
    printf("6 -> Exibir livros em pos-ordem\n");
    printf("7 -> Encerrar\n");
    printf("Digite uma opcao: ");
    scanf("%d", &opc);
    return opc;
}

Nodo* handleInsert(Nodo* root) {
    Book* book = createBook();
    root = insert(root, book);
}

Nodo* handleDelete(Nodo* root) {
    //Verifica se o livro existe
    int issn; 
    printf("Digite o ISSN: ");
    scanf("%d", &issn);
    Nodo* nodo = search(root, issn);
    if (!nodo) printf("Elemento nao existe!!\n");
    else {
        printf("Elemento deletado %d !\n", nodo->book->issn);
        root = delete(root, nodo->book);
    }
    return root;
}

void handleSearch(Nodo* root) {
    int issn;
    printf("Digite o ISSN: ");
    scanf("%d", &issn);
    // Procura nodo na árvore binária
    Nodo* nodo = search(root, issn);
    if (!nodo) printf("Elemento nao existe!!\n");
    else {
        displayBook(nodo->book);
    }
}

Nodo* handleSelect(Nodo* root, int opc) {
    switch(opc) {
        // Inserir
        case 1: {
            root = handleInsert(root);
            break;
        }
        // Deletar
        case 2: {
            root = handleDelete(root);
            break;
        }
        // Pesquisar por ISSN
        case 3: {
            handleSearch(root);
            break;
        }   
        // Exibir em ordem
        case 4: {
            order(root);
            break;
        }
        // Exibir em pré-ordem
        case 5: {
            preOrder(root);
            break;
        }
        // Exibir em pós-ordem
        case 6: {
            posOrder(root);
            break;
        }
        // Encerrar
        case 7: {
            root = deleteAll(root);
            printf("Programa Encerrado!!\n");
            break;
        }
        default: {
            printf("Opcao invalida\n");
        }
    }
    return root;
}


