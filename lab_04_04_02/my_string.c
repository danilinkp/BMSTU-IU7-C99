#include "my_string.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define INPUT_STR_ERROR 1
#define LEN_STR_ERROR 2
#define LEN_STRING_ERROR -1


int split(words_t words, string_t s)
{
    size_t curr_word_len = 0;
    int words_len = 0;
    for (size_t i = 0; i < strlen(s); i++)
    {
        if (isspace(s[i]))
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

    if (strlen(tmp_string) > MAX_STRING_LENGTH)
        return LEN_STR_ERROR;

    strcpy(s, tmp_string);

    return EXIT_SUCCESS;
}

int is_in_month_30(string_t s, char months_30[][9])
{
    int is_moths_30 = 0;
    for (size_t i = 0; i < 4; i++)
    {
        if (strcmp(s, months_30[i]) == 0)
            is_moths_30 = 1;
    }
    return is_moths_30;
}

int is_in_month_31(string_t s, char months_31[][8])
{
    int is_months_31 = 0;
    for (size_t i = 0; i < 7; i++)
    {
        if (strcmp(s, months_31[i]) == 0)
            is_months_31 = 1;
    }
    return is_months_31;
}

int to_int(string_t s)
{
    int is_number = 1;
    for (size_t i = 0; i < strlen(s); i++)
        if (!isdigit(s[i]))
            is_number = 0;
    if (!is_number)
        return 0;
    return atoi(s);
}

int is_leap(int year)
{
    return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

void lower(string_t str)
{
    for (size_t i = 0; i < strlen(str); i++)
        str[i] = tolower(str[i]);
}

int is_data(words_t words)
{
    int is_data = 0;
    char months_30[][9] = { "april", "june", "september", "november" };
    char months_31[][8] = { "january", "march", "may", "july", "august", "october", "december" };
    int day = to_int(words[0]);
    int year = to_int(words[2]);
    string_t month;
    strcpy(month, words[1]);
    lower(month);
    if (is_in_month_30(month, months_30))
    {
        if ((day > 0 && day <= 30) && (year > 0 && year < 10000))
            is_data = 1;
    }
    else if (is_in_month_31(month, months_31))
    {
        if ((day > 0 && day <= 31) && (year > 0 && year < 10000))
            is_data = 1;
    }
    else if (strcmp(month, "february") == 0)
    {
        if (is_leap(year))
        {
            if ((day > 0 && day <= 29) && (year > 0 && year < 10000))
                is_data = 1;
        }
        else
        {
            if ((day > 0 && day <= 28) && (year > 0 && year < 10000))
                is_data = 1;
        }
    }
    return is_data;
}