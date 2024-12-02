#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

#define ERROR_A 1
#define ERROR_N 2

uint32_t cyclic_shift_left(uint32_t a, int n)
{
    return (a << n) | (a >> (32 - n));
}


void print_bin(uint32_t num)
{
    for (int i = 32 - 1; i >= 0; i--)
        printf("%d", (num >> i) & 1);
    printf("\n");
}


int main(void)
{
    uint32_t a;
    int n;

    printf("Enter a: ");
    if (scanf("%"SCNu32, &a) != 1)
    {
        printf("Error: valid a\n");
        return ERROR_A;
    }

    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n < 0)
    {
        printf("Error: not valid n\n");
        return ERROR_N;
    }

    uint32_t result = cyclic_shift_left(a, n);

    printf("Result: ");
    print_bin(result);

    return EXIT_SUCCESS;
}
