#include "my_string.h"
#include <stdio.h>

#define INPUT_STR_ERROR 1
#define LEN_STRING_ERROR -1

int main(void)
{
    string_t s;
    int rc = input_line(s);
    if (rc == INPUT_STR_ERROR)
    {
        printf("NO");
        return 0;
    }
    if (rc != EXIT_SUCCESS)
        return rc;
    

    words_t words;
    int words_len = split(words, s);
    if (words_len == LEN_STRING_ERROR)
    {
        printf("Слово превышает максмиально разрешенную длину.");
        return LEN_STRING_ERROR;
    }

    if (words_len != 3)
        printf("NO");
    else
    {
        if (is_data(words))
            printf("YES");
        else
            printf("NO");
    }

    return EXIT_SUCCESS;
}