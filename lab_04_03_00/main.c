#include <stdio.h>
#include <string.h>
#include "my_string.h"
#define LEN_STRING_ERROR -1
#define EMPTY_STR_ERROR 3

int main(void)
{
    string_t s1;
    printf("Введите строку: ");
    int rc1 = input_line(s1);
    if (rc1 != EXIT_SUCCESS)
        return rc1;

    words_t words;
    int words_len = split(words, s1);
    if (words_len == LEN_STRING_ERROR || words_len == 0)
    {
        printf("Слово превышает максмиально разрешенную длину.");
        return LEN_STRING_ERROR;
    }

    string_t s2;
    size_t len_s2 = make_str(words, s2, words_len);

    if (len_s2 > 0)
        printf("Result: %s\n", s2);
    else
    {
        printf("Строка пустая.");
        return EMPTY_STR_ERROR;
    }
    return EXIT_SUCCESS;
}
