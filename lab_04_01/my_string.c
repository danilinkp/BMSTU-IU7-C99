#include <stdlib.h>
#include <string.h>

size_t my_strlen(const char *s)
{
    size_t len = 0;
    while (s[len] != '\0')
    {
        len++;
    }
    return len;
}

char *my_strpbrk(const char *s1, const char *s2)
{
    for (size_t i = 0; i < my_strlen(s2); i++)
        for (size_t j = 0; j < my_strlen(s1); j++)
            if (s1[j] == s2[i])
                return (char *)s1 + j;
    return NULL;
}

size_t my_strspn(const char *s1, const char *s2)
{
    size_t len = 0;
    for (size_t i = 0; i < my_strlen(s1); i++)
    {
        int is_chr_in_s2 = 0;
        for (size_t j = 0; j < my_strlen(s2); j++)
        {
            if (s1[i] == s2[j])
                is_chr_in_s2 = 1;
        }
        if (is_chr_in_s2)
            len++;
        else
            return len;
    }
    return len;
}

size_t my_strcspn(const char *s1, const char *s2)
{
    size_t len = 0;
    for (size_t i = 0; i < my_strlen(s1); i++)
    {
        int is_chr_in_s2 = 0;
        for (size_t j = 0; j < my_strlen(s2); j++)
        {
            if (s1[i] == s2[j])
                is_chr_in_s2 = 1;
        }
        if (!is_chr_in_s2)
            len++;
        else
            return len;
    }
    return len;
}

char *my_strchr(const char *s, int c)
{
    if (c == 0)
        return (char*)s + my_strlen(s);

    for (size_t i = 0; i < my_strlen(s); i++)
        if (s[i] == c)
            return (char*)s + i;
    return NULL;
}

char *my_strrchr(const char *s, int c)
{
    if (c == 0)
        return (char*)s + my_strlen(s);

    char *curr = NULL;
    for (size_t i = 0; i < my_strlen(s); i++)
        if (s[i] == c)
            curr = (char*)s + i;
    return curr;
}
