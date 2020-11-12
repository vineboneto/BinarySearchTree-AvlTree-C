#ifndef BOOK_H
#define BOOK_H

typedef struct sBook {
    int issn;
    int year;
    char* name;
} Book;

Book* createBook();
void getDataBook(Book*);
void displayBook(Book*);

#endif