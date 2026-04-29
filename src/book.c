/* book.c */

/*
 * Реализация функций для работы с текстовыми файлами и структурой BOOK.
 * Сервер: чтение/запись файлов, фильтрация и вывод данных.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "book.h"

/*
 * Чтение данных о книгах из текстового файла.
 * Формат каждой записи: 7 строк (одно поле на строку).
 * Возвращает количество прочитанных записей.
 */
int
read_books_from_file(const char *filename, BOOK books[], int max)
{
        FILE   *f;
        int     n = 0;

        f = fopen(filename, "r");
        if (f == NULL) {
                fprintf(stderr, "Ошибка: не удаётся открыть файл '%s'\n",
                        filename);
                return 0;
        }

        while (n < max) {
                char buf[MAX_STR_LEN];

                /* Чтение названия */
                if (fgets(books[n].title, MAX_STR_LEN, f) == NULL)
                        break;
                books[n].title[strcspn(books[n].title, "\n")] = '\0';

                /* Чтение фамилии автора */
                if (fgets(books[n].author.last_name, MAX_STR_LEN, f) == NULL)
                        break;
                books[n].author.last_name[strcspn(
                        books[n].author.last_name, "\n")] = '\0';

                /* Чтение имени автора */
                if (fgets(books[n].author.first_name, MAX_STR_LEN, f) == NULL)
                        break;
                books[n].author.first_name[strcspn(
                        books[n].author.first_name, "\n")] = '\0';

                /* Чтение года */
                if (fgets(buf, MAX_STR_LEN, f) == NULL)
                        break;
                books[n].year = atoi(buf);

                /* Чтение издательства */
                if (fgets(books[n].publisher, MAX_STR_LEN, f) == NULL)
                        break;
                books[n].publisher[strcspn(books[n].publisher, "\n")] = '\0';

                /* Чтение себестоимости, цены, прибыли */
                if (fgets(buf, MAX_STR_LEN, f) == NULL) break;
                books[n].cost = atof(buf);
                if (fgets(buf, MAX_STR_LEN, f) == NULL) break;
                books[n].price = atof(buf);
                if (fgets(buf, MAX_STR_LEN, f) == NULL) break;
                books[n].profit = atof(buf);

                n++;
        }

        fclose(f);
        return n;
}

/*
 * Запись данных о книгах в текстовый файл.
 * Формат: одно поле на строку.
 */
void
write_books_to_file(const char *filename, BOOK books[], int n)
{
        FILE *f;

        f = fopen(filename, "w");
        if (f == NULL) {
                fprintf(stderr, "Ошибка: не удаётся создать файл '%s'\n",
                        filename);
                return;
        }

        for (int i = 0; i < n; i++) {
                fprintf(f, "%s\n", books[i].title);
                fprintf(f, "%s\n", books[i].author.last_name);
                fprintf(f, "%s\n", books[i].author.first_name);
                fprintf(f, "%d\n", books[i].year);
                fprintf(f, "%s\n", books[i].publisher);
                fprintf(f, "%.2f\n", books[i].cost);
                fprintf(f, "%.2f\n", books[i].price);
                fprintf(f, "%.2f\n", books[i].profit);
        }

        fclose(f);
        printf("Данные сохранены в файл '%s' (%d записей).\n", filename, n);
}

/*
 * Вывод всех книг в виде таблицы на экран.
 */
void
print_books(BOOK books[], int n)
{
        printf("\n%-30s %-15s %-12s %6s %-15s %10s %10s %10s\n",
                "Название", "Фамилия", "Имя", "Год",
                "Издательство", "Себест.", "Цена", "Прибыль");
        printf("%s\n",
                "----------------------------------------------------------------------"
                "-------------------------------");

        for (int i = 0; i < n; i++) {
                printf("%-30s %-15s %-12s %6d %-15s %10.2f %10.2f %10.2f\n",
                        books[i].title,
                        books[i].author.last_name,
                        books[i].author.first_name,
                        books[i].year,
                        books[i].publisher,
                        books[i].cost,
                        books[i].price,
                        books[i].profit);
        }
}

/*
 * Вывод книг, фамилия автора которых начинается с заданной буквы.
 */
/*
 * Проверяет, начинается ли строка с кириллической буквы К (UTF-8).
 * UTF-8 код К = 0xD0 0x9A, к = 0xD0 0xBА.
 */
static int
starts_with_k(const char *s)
{
        const unsigned char *u = (const unsigned char *)s;

        /* Заглавная К = D0 9A, строчная к = D0 BA */
        if (u[0] == 0xD0 && (u[1] == 0x9A || u[1] == 0xBA))
                return 1;
        /* Латинская K / k */
        if (u[0] == 'K' || u[0] == 'k')
                return 1;
        return 0;
}

void
print_books_by_author_letter(BOOK books[], int n, char letter)
{
        int     found = 0;

        (void)letter; /* буква зафиксирована в условии варианта: К */

        printf("\nКниги авторов, фамилия которых начинается с 'К':\n");
        printf("%-30s %-15s %-12s %6s %-15s %10s\n",
                "Название", "Фамилия", "Имя", "Год",
                "Издательство", "Цена");
        printf("%s\n",
                "----------------------------------------------------------------------"
                "--");

        for (int i = 0; i < n; i++) {
                if (starts_with_k(books[i].author.last_name)) {
                        printf("%-30s %-15s %-12s %6d %-15s %10.2f\n",
                                books[i].title,
                                books[i].author.last_name,
                                books[i].author.first_name,
                                books[i].year,
                                books[i].publisher,
                                books[i].price);
                        found = 1;
                }
        }

        if (!found)
                printf("  Книги таких авторов не найдены.\n");
}

/*
 * Просмотр содержимого текстового файла.
 */
void
view_file(const char *filename)
{
        FILE   *f;
        char    buf[256];

        f = fopen(filename, "r");
        if (f == NULL) {
                fprintf(stderr, "Ошибка: не удаётся открыть файл '%s'\n",
                        filename);
                return;
        }

        printf("\n=== Содержимое файла '%s' ===\n", filename);
        while (fgets(buf, sizeof(buf), f) != NULL)
                printf("%s", buf);
        printf("=== Конец файла ===\n");

        fclose(f);
}