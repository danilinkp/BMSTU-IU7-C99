#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdlib.h>

#define MAX_STRING_LENGTH 256
#define MAX_WORD_LENGTH 16

typedef char words_t[MAX_STRING_LENGTH][MAX_WORD_LENGTH + 1];
typedef char string_t[MAX_STRING_LENGTH + 1];

int split(words_t words, string_t s);
int input_line(string_t s);
size_t make_str(words_t words, string_t s, int words_len);

#endif
