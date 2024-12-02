#include "my_string.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define INPUT_STR_ERROR 1
#define LEN_STR_ERROR 2
#define LEN_STRING_ERROR -1

int is_separator(char c)
{
    if (isspace(c) || ispunct(c))
        return 1;
    return 0;
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

size_t remove_chars(string_t s)
{
    size_t c = 0;
    for (size_t i = 1; i < strlen(s); i++)
    {
        if (s[i] == s[0])
            c++;
        else
            s[i - c] = s[i];
    }
    return strlen(s) - c;
}

void reverse(words_t words, int words_len)
{
    string_t temp;
    for (int i = 0; i < words_len / 2; i++)
    {
        strcpy(temp, words[i]);
        strcpy(words[i], words[words_len - i - 1]);
        strcpy(words[words_len - i - 1], temp);
    }
}

size_t make_str(words_t words, string_t s, int words_len)
{
    size_t len_s = 0;
    reverse(words, words_len);
    for (int i = 1; i < words_len; i++)
    {
        if (strcmp(words[i], words[0]) != 0)
        {
            size_t len_of_new_word = remove_chars(words[i]);
            for (size_t j = 0; j < len_of_new_word; j++)
            {
                s[len_s] = words[i][j];
                len_s++;
            }
            if (i != (words_len - 1) && len_of_new_word > 0)
            {
                s[len_s] = ' ';
                len_s++;
            }
        }
    }
    s[len_s] = '\0';
    return len_s;
}
