#ifndef BOOK_H
#define BOOK_H

/* Estrutura do livro */
typedef struct sBook {
    int issn;
    int year;
    char* name;
} Book;

/* Cria uma novo registro de Livro */
Book* createBook();
/* Configura os dados do livro */
void setDataBook(Book*);
/* Exibe os dados do livro */
void displayBook(Book*);

#endif