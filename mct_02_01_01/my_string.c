#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "my_string.h"

#define INPUT_STR_ERROR 1
#define LEN_STR_ERROR 2


void clear(words_t words, int len)
{
    for (int i = 0; i < len; i++)
        strcpy(words[i], "");
}

int trim_spaces(string_t s, words_t words)
{
    char *p = strtok(s, " ");
    int i = 0;
    while (p != NULL)
    {
        strcpy(words[i], p);
        p = strtok(NULL, " ");
        i++;
    }
    if (i > MAX_WORD_LENGTH)
        return LEN_STR_ERROR;
    return i;
}


int input_line(string_t s)
{
    char tmp_string[MAX_STRING_LENGTH + 2];

    if (!fgets(tmp_string, MAX_STRING_LENGTH + 2, stdin))
        return INPUT_STR_ERROR;

    tmp_string[strcspn(tmp_string, "\n")] = '\0';

    if (strlen(tmp_string) == 0 || strlen(tmp_string) > MAX_STRING_LENGTH)
        return LEN_STR_ERROR;

    strcpy(s, tmp_string);

    return EXIT_SUCCESS;
}

int is_number(string_t s)
{
    int is_number = 1;
    for (size_t i = 0; i < strlen(s); i++)
        if (!isdigit(s[i]))
            is_number = 0;
    return is_number;
}

int is_zeros(string_t s)
{
    int is_zero = 1;
    if (strlen(s) >= 4)
    {
        for (size_t i = 0; i < 4; i++)
        {
            if (s[i] != '0')
                is_zero = 0;
        }
    }
    else
        is_zero = 0;

    return is_zero;
}