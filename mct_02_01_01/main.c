#include <stdio.h>
#include "my_string.h"
#include <string.h>
#include <stdlib.h>

int main(void)
{
    string_t s;
    words_t words;

    printf("Введите строку: ");
    int rc = input_line(s);
    if (rc != EXIT_SUCCESS)
        return rc;

    while (! is_zeros(s))
    {
        int len_words = trim_spaces(s, words);
        if (len_words == LEN_STRING_ERROR)
        {
            printf("Неверное кол-во слов\n");
            return LEN_STRING_ERROR;
        }
        for (int i = 0; i < len_words; i++)
            if (is_number(words[i]))
                printf("%s\n", words[i]);
        int rc = input_line(s);
        if (rc != EXIT_SUCCESS)
            return rc;
        
        clear(words, len_words);
    }

    return EXIT_SUCCESS;

}