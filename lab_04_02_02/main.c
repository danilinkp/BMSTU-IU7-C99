#include <stdio.h>
#include <string.h>
#include "my_string.h"
#define LEN_STRING_ERROR -1

int main(void)
{
    string_t s1;
    printf("Введите первую строку: ");
    int rc1 = input_line(s1);
    if (rc1 != EXIT_SUCCESS)
        return rc1;

    words_t words_1;
    int words_1_len = split(words_1, s1);
    if (words_1_len == LEN_STRING_ERROR || words_1_len == 0)
    {
        printf("Слово превышает максмиально разрешенную длину.");
        return LEN_STRING_ERROR;
    }

    string_t s2;
    printf("Введите вторую строку: ");
    int rc2 = input_line(s2);
    if (rc2 != EXIT_SUCCESS)
        return rc2;

    words_t words_2;
    int words_2_len = split(words_2, s2);
    if (words_2_len == LEN_STRING_ERROR || words_2_len == 0)
    {
        printf("Слово превышает максмиально разрешенную длину.");
        return LEN_STRING_ERROR;
    }

    for (int i = 0; i < words_1_len; i++)
    {
        int is_in_second_line = 0;
        if (is_unique(words_1, words_1[i], i))
        {
            for (int k = 0; k < words_2_len; k++)
                if (strcmp(words_1[i], words_2[k]) == 0)
                    is_in_second_line = 1;
            if (is_in_second_line)
                printf("Result: %s yes\n", words_1[i]);
            else
                printf("Result: %s no\n", words_1[i]);
        }
    }

    return EXIT_SUCCESS;
}
