#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    int num_entrance, num_floor;

    printf("Enter the number of flat: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Error input");
        return EXIT_FAILURE;
    }

    num_entrance = ((n - 1) / 36) + 1;
    num_floor = ((n - 1) % 36) / 4 + 1;

    printf("Number of entrance is: %d\n", num_entrance);
    printf("Number of floor is: %d", num_floor);

    return EXIT_SUCCESS;
}
