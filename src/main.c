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

int menu();

Nodo* createNodo();
Book* createBook();
Nodo* insert(Nodo*, Book*);
Nodo* delete (Nodo*, Book*);
Nodo* deleteAll(Nodo*);

void getDataBook();
void displayBook(Book*);

Nodo* search(Nodo*, Book*);
void order(Nodo*);
void preOrder(Nodo*);
void posOrder(Nodo*);

int main () {

    Nodo* root = NULL;
    Book* book = createBook();
    root = insert(root, book);

    root = deleteAll(root);
    system("pause");
    return 0;
}

int menu() {
    int opc;
    printf("1 -> Inserir livro\n");
    printf("2 -> Deletar livro\n");
    printf("3 -> Pesquisar livro por ISSN\n");
    printf("4 -> Exibir livros em ordem\n");
    printf("4 -> Exibir livros em pré-ordem\n");
    printf("4 -> Exibir livros em pós-ordem\n");
    printf("Digite uma opcao: ");
    scanf("%d", &opc);
    return opc;
}

Nodo* createNodo() {
    Nodo* n = NULL;
    n = (Nodo*) malloc(sizeof(Nodo));
    n->left = n->right = NULL;
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
    getDataBook(b);
    return b;
}

void getDataBook(Book* b) {
    printf("ISSN: ");
    scanf("%d", &b->issn);
    printf("Name: ");
    scanf(" %[^\n]", b->name);
    printf("Year: ");
    scanf("%d", &b->year);
}

Nodo* insert(Nodo* root, Book* book) {
    if (!root) {
        printf("Entrou aqui.\n");
        root = createNodo();
        root->book = book;
    } 
    else if (book->issn < root->book->issn) root->left = insert(root->left, book);
    else root->right = insert(root->right, book);

    return root;
}

Nodo* delete(Nodo* root, Book* book) {
    if (!root) return NULL;
    else if (root->book->issn > book->issn) root->left = delete(root->left, book);
    else if (root->book->issn < book->issn) root->right = delete(root->right, book);
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
            root->book = aux->book; // troca informações
            aux->book = book;
            root->right = delete(root->right, book);
        }
    }

    return root;
}

Nodo* search(Nodo* root, Book* book) {
    if (!root) return NULL;
    else if (root->book->issn > book->issn) return search(root->left, book);
    else if (root->book->issn < book->issn) return search(root->right, book);
    else return root;
}

Nodo* deleteAll(Nodo* root) {
    if (root) {
        root->left = deleteAll(root->left);
        root->right = deleteAll(root->right);
        printf("Elemento deletado %d\n", root->book->issn);
        free(root);
        free(root->book);
        free(root->book->name);
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

void preOrder(Nodo* nodo) {
    if (nodo) {
        displayBook(nodo->book);
        preOrder(nodo->left);
        preOrder(nodo->right);
    }
}

void posOrder(Nodo* nodo) {
    if (nodo) {
        posOrder(nodo->left);
        posOrder(nodo->right);
        displayBook(nodo->book);
    }
}

void displayBook(Book* book) {
    printf("issn: %d\n", book->issn);
    printf("name: %s\n", book->name);
    printf("year: %d\n", book->year);
}