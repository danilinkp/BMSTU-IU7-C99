#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdlib.h>

char *my_strpbrk(const char *s1, const char *s2);
size_t my_strspn(const char *s1, const char *s2);
size_t my_strcspn(const char *s1, const char *s2);
char *my_strchr(const char *s, int c);
char *my_strrchr(const char *s, int c);

#endif