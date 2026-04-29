/* book.h */

#ifndef BOOK_H
#define BOOK_H

/*
 * Заголовочный файл для модуля «Книга».
 * Структура BOOK: название, автор (фамилия, имя), год выхода,
 * издательство, себестоимость, цена, прибыль.
 */

#define MAX_BOOKS       50
#define MAX_STR_LEN     100

/* Структура автора */
typedef struct {
        char    last_name[MAX_STR_LEN];  /* фамилия */
        char    first_name[MAX_STR_LEN]; /* имя */
} Author;

/* Структура книги */
typedef struct {
        char    title[MAX_STR_LEN];      /* название */
        Author  author;                  /* автор */
        int     year;                    /* год выхода */
        char    publisher[MAX_STR_LEN];  /* издательство */
        double  cost;                    /* себестоимость */
        double  price;                   /* цена */
        double  profit;                  /* прибыль */
} BOOK;

/* Объявления функций */
int     read_books_from_file(const char *filename, BOOK books[], int max);
void    write_books_to_file(const char *filename, BOOK books[], int n);
void    print_books(BOOK books[], int n);
void    print_books_by_author_letter(BOOK books[], int n, char letter);
void    view_file(const char *filename);

#endif /* BOOK_H */