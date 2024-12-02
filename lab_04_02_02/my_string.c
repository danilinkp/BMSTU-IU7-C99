#include "my_string.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define INPUT_STR_ERROR 1
#define LEN_STR_ERROR 2
#define LEN_STRING_ERROR -1

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


int is_separator(char c)
{
    if (isspace(c) || ispunct(c))
        return 1;
    return 0;
}

int is_unique(words_t words, string_t s, int words_len)
{
    int count_string_in_words = 1;
    for (int i = 0; i < words_len; i++)
    {
        if (strcmp(s, words[i]) == 0)
            count_string_in_words++;
    }
    return count_string_in_words == 1;
}

int split(words_t words, string_t s)
{
    size_t curr_word_len = 0;
    int words_len = 0;
    for (size_t i = 0; i < strlen(s); i++)
    {
        if (is_separator(s[i]))
        {
            if (curr_word_len)
            {
                words[words_len][curr_word_len] = '\0';
                words_len++;
                curr_word_len = 0;
            }
            continue;
        }
        words[words_len][curr_word_len] = s[i];
        curr_word_len++;

        if (curr_word_len > MAX_WORD_LENGTH)
            return LEN_STRING_ERROR;
    }

    if (curr_word_len)
    {
        words[words_len][curr_word_len] = '\0';
        words_len++;
    }

    return words_len;
}