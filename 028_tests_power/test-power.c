#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned base, unsigned exponent);

int check(unsigned base, unsigned exponent, unsigned expected_result)
{
    if (power(base, exponent) != expected_result)
    {
        printf("Exit with an error in power(%u,%u)!\n", base, exponent);
        exit(EXIT_FAILURE);
    }
}

int main()
{
    check(5, 3, 125);
    check(888888, 1, 888888);
    check(2, 0, 1);
    check(1, 2, 1);
    check(1, 1, 1);
    check(0, 0, 1);
    return EXIT_SUCCESS;
}