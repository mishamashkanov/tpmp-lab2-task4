/* main.c */

/*
 * Клиент: демонстрирует работу с текстовыми файлами и структурой BOOK.
 * Задание 4, Вариант 16: вывести книги авторов, фамилия которых
 * начинается с буквы "К".
 */

#include <stdio.h>
#include "book.h"

#define INPUT_FILE   "docs/books.txt"
#define OUTPUT_FILE  "docs/result.txt"

int
main(void)
{
        BOOK    books[MAX_BOOKS];
        BOOK    filtered[MAX_BOOKS];
        int     n;
        int     fcount = 0;

        printf("=== Каталог книг (Вариант 16) ===\n");

        /* Просмотр исходного файла */
        view_file(INPUT_FILE);

        /* Чтение данных из файла */
        n = read_books_from_file(INPUT_FILE, books, MAX_BOOKS);
        if (n == 0) {
                printf("Файл пуст или не удалось прочитать данные.\n");
                return 1;
        }
        printf("\nПрочитано записей: %d\n", n);

        /* Вывод всех книг */
        printf("\n--- Все книги ---");
        print_books(books, n);

        /* Фильтрация: авторы с фамилией на 'К' */
        print_books_by_author_letter(books, n, 'K');

        /* Сохранение отфильтрованных данных в новый файл */
        for (int i = 0; i < n; i++) {
                /* Сравниваем первые два байта UTF-8 кириллической К */
                const unsigned char *s =
                        (const unsigned char *)books[i].author.last_name;

                if ((s[0] == 0xD0 && s[1] == 0x9A) || /* К заглавная */
                    (s[0] == 'K')) {
                        filtered[fcount++] = books[i];
                }
        }
        write_books_to_file(OUTPUT_FILE, filtered, fcount);

        /* Просмотр результирующего файла */
        view_file(OUTPUT_FILE);

        return 0;
}