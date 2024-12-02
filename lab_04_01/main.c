#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void)
{
    int pos_count = 0;
    int count = 0;
    // test my_strpbrk
    {
        {
            char *s1 = "hello123";
            char *s2 = "0123456789";
            if (strpbrk(s1, s2) == my_strpbrk(s1, s2))
                pos_count++;
            count++;
        }

        {
            char *s1 = "hello123";
            char *s2 = "@";
            if (strpbrk(s1, s2) == my_strpbrk(s1, s2))
                pos_count++;
            count++;
        }

        {
            char *s1 = "hello123";
            char *s2 = "";
            if (strpbrk(s1, s2) == my_strpbrk(s1, s2))
                pos_count++;
            count++;
        }

        {
            char *s1 = "";
            char *s2 = "";
            if (strpbrk(s1, s2) == my_strpbrk(s1, s2))
                pos_count++;
            count++;
        }
    }

    // test my_strspn
    {
        {
            char *s1 = "hello123";
            char *s2 = "myhellyea";
            if (strspn(s1, s2) == my_strspn(s1, s2))
                pos_count++;
            count++;
        }

        {
            char *s1 = "hello123";
            char *s2 = "qwerty";
            if (strspn(s1, s2) == my_strspn(s1, s2))
                pos_count++;
            count++;
        }

        {
            char *s1 = "hello123";
            char *s2 = "";
            if (strspn(s1, s2) == my_strspn(s1, s2))
                pos_count++;
            count++;
        }

        {
            char *s1 = "";
            char *s2 = "";
            if (strspn(s1, s2) == my_strspn(s1, s2))
                pos_count++;
            count++;;
        }
    }

    // test my_strcspn
    {
        {
            char *s1 = "hello123";
            char *s2 = "myhellyea";
            if (strcspn(s1, s2) == my_strcspn(s1, s2))
                pos_count++;
            count++;
        }

        {
            char *s1 = "hello123";
            char *s2 = "qwerty";
            if (strcspn(s1, s2) == my_strcspn(s1, s2))
                pos_count++;
            count++;
        }

        {
            char *s1 = "hello123";
            char *s2 = "";
            if (strcspn(s1, s2) == my_strcspn(s1, s2))
                pos_count++;
            count++;
        }

        {
            char *s1 = "";
            char *s2 = "";
            if (strcspn(s1, s2) == my_strcspn(s1, s2))
                pos_count++;
            count++;
        }
    }
    
    // test my_strchr
    {
        {
            char *s1 = "hello123";
            char s2 = 'l';
            if (strchr(s1, s2) == my_strchr(s1, s2))
                pos_count++;
            count++;
        }

        {
            char *s1 = "hello123";
            char s2 = 'z';
            if (strchr(s1, s2) == my_strchr(s1, s2))
                pos_count++;
            count++;
        }

        {
            char *s1 = "hello123";
            char s2 = '\0';
            if (strchr(s1, s2) == my_strchr(s1, s2))
                pos_count++;
            count++;
        }

        {
            char *s1 = "";
            char s2 = '\0';
            if (strchr(s1, s2) == my_strchr(s1, s2))
                pos_count++;
            count++;
        }
    }

    // test my_strrchr
    {
        {
            char *s1 = "hello123";
            char s2 = 'l';
            if (strrchr(s1, s2) == my_strrchr(s1, s2))
                pos_count++;
            count++;
        }

        {
            char *s1 = "hello123";
            char s2 = 'z';
            if (strrchr(s1, s2) == my_strrchr(s1, s2))
                pos_count++;
            count++;
        }

        {
            char *s1 = "hello123";
            char s2 = '\0';
            if (strrchr(s1, s2) == my_strrchr(s1, s2))
                pos_count++;
            count++;
        }

        {
            char *s1 = "";
            char s2 = '\0';
            if (strrchr(s1, s2) == my_strrchr(s1, s2))
                pos_count++;
            count++;
        }
    }

    printf("%d", count - pos_count);
    return count - pos_count;
}
