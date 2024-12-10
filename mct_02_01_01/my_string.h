#ifndef MY_STRING_H

#define MY_STRING_H

#define MAX_STRING_LENGTH 1000000
#define MAX_WORD_LENGTH 16
#define LEN_STRING_ERROR -1

typedef char words_t[MAX_STRING_LENGTH][MAX_WORD_LENGTH + 1];
typedef char string_t[MAX_STRING_LENGTH];


int input_line(string_t s);
int is_number(string_t s);
int trim_spaces(string_t s, words_t words);
int is_zeros(string_t s);
void clear(words_t words, int len);

#endif