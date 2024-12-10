#include "my_string.h"
#include <stdarg.h>
#include <limits.h>

size_t my_strlen(const char *s)
{
    size_t len = 0;
    while (s[len] != '\0')
        len++;
    return len;
}

void reverse(char *str)
{
    size_t len = my_strlen(str);
    for (size_t i = 0; i < (len / 2); i++)
    {
        char tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
}

void int_to_str(long num, char *str)
{
    size_t i = 0;
    int is_long_min = 0;
    if (num == LONG_MIN)
    {
        num = LONG_MIN + 1;
        is_long_min = 1;
    }
    if (num < 0)
    {
        str[i++] = '-';
        num = -num;
    }
    do
    {
        str[i++] = (char) ((num % 10) + '0');
        num /= 10;
    }
    while (num != 0);
    if (is_long_min)
        str[1] = (char) ((int) str[1] + 1);
    str[i] = '\0';
    if (str[0] == '-')
        reverse(str + 1);
    else
        reverse(str);
}

void dec_to_str_oct(unsigned int num, char *str)
{
    size_t i = 0;
    do
    {
        str[i++] = (char) ((num % 8) + '0');
        num /= 8;
    }
    while (num != 0);

    str[i] = '\0';
    reverse(str);
}

int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...)
{
    va_list vl;
    va_start(vl, format);
    int decimal_num;
    unsigned int oct_num;
    long decimal_long;
    size_t written_len = 0;
    int total_len = 0;
    size_t i = 0;
    while (format[i] != '\0')
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == 'd')
            {
                decimal_num = va_arg(vl, int);
                char str_num[12];
                int_to_str(decimal_num, str_num);
                for (size_t j = 0; j < my_strlen(str_num); j++)
                {
                    if (written_len + 1 < n)
                        s[written_len++] = str_num[j];
                    total_len++;
                }
                i++;
            }
            else if (format[i] == 'l' && format[i + 1] == 'd')
            {
                decimal_long = va_arg(vl, long long);
                char str_long[22];
                int_to_str(decimal_long, str_long);
                for (size_t j = 0; j < my_strlen(str_long); j++)
                {
                    if (written_len + 1 < n)
                        s[written_len++] = str_long[j];
                    total_len++;
                }
                i += 2;
            }
            else if (format[i] == 'o')
            {
                oct_num = va_arg(vl, unsigned int);
                char str_oct[12];
                dec_to_str_oct(oct_num, str_oct);
                for (size_t j = 0; j < my_strlen(str_oct); j++)
                {
                    if (written_len + 1 < n)
                        s[written_len++] = str_oct[j];
                    total_len++;
                }
                i++;
            }
            else
            {
                if (written_len + 1 < n)
                    s[written_len++] = '%';
                total_len++;
                if (written_len + 1 < n)
                    s[written_len++] = format[i];
                total_len++;
                i++;
            }
        }
        else
        {
            if (written_len + 1 < n)
                s[written_len++] = format[i];
            total_len++;
            i++;
        }
    }
    if (n > 0)
    {
        if (written_len < n)
            s[written_len] = '\0';
        else
            s[n - 1] = '\0';
    }
    va_end(vl);
    return total_len;
}
