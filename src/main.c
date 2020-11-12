#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int menu();

int main () {
    system("cls");
    Nodo* root = NULL;

    int opc = 0;
    while (opc != 7) {
        opc = menu();
        switch(opc) {
            // Inserir
            case 1: {
                Book* book = createBook();
                root = insert(root, book);
                break;
            }
            // Deletar
            case 2: {
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
                break;
            }
            // Pesquisar por ISSN
            case 3: {
                int issn;
                printf("Digite o ISSN: ");
                scanf("%d", &issn);
                Nodo* nodo = search(root, issn);
                if (!nodo) printf("Elemento nao existe!!\n");
                else {
                    displayBook(nodo->book);
                }
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
        system("pause");
        system("cls");
    }

    root = deleteAll(root);
    return 0;
}

int menu() {
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



