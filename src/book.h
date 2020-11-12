#include <stdio.h>
#include <stdlib.h>

typedef struct sBook {
    int issn;
    int year;
    char* name;
} Book;

Book* createBook();
void getDataBook();
void displayBook(Book*);

Book* createBook() {
    Book* b = NULL;
    size_t bytes = 256;
    b = (Book*) malloc(sizeof(Book));
    if (!b) {
        exit(EXIT_FAILURE);
        perror("Overflow!!");
    }
    b->name = (char*) malloc(bytes);
    getDataBook(b);
    return b;
}

void displayBook(Book* book) {
    printf("issn: %d\n", book->issn);
    printf("name: %s\n", book->name);
    printf("year: %d\n\n", book->year);
}

void getDataBook(Book* b) {
    printf("ISSN: ");
    scanf("%d", &b->issn);
    printf("Name: ");
    scanf(" %[^\n]", b->name);
    printf("Year: ");
    scanf("%d", &b->year);
}