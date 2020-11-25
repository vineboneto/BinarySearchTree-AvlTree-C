#include <stdio.h>
#include <stdlib.h>
#include "../headers/book.h"

Book* createBook() {
    Book* b = NULL;
    size_t bytes = 256;
    b = (Book*) malloc(sizeof(Book));
    if (!b) {
        exit(EXIT_FAILURE);
        perror("Overflow!!");
    }
    b->name = (char*) malloc(bytes);
    setDataBook(b);
    return b;
}

void displayBook(Book* book) {
    printf("ISSN: %d\n", book->issn);
    printf("Nome: %s\n", book->name);
    printf("Ano: %d\n\n", book->year);
}

void setDataBook(Book* b) {
    printf("ISSN: ");
    scanf("%d", &b->issn);
    printf("Nome: ");
    scanf(" %[^\n]", b->name);
    printf("Ano: ");
    scanf("%d", &b->year);
}