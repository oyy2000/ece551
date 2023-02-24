#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int *array, size_t n);

void check(int *array, size_t n, size_t expected_result)
{
    size_t ret = maxSeq(array, n);
    printf("expect %zu, got %zu\n", expected_result, ret);
    if (ret != expected_result)
    {
        printf("Exit with error!\n");
        exit(EXIT_FAILURE);
    }
}

int main()
{

    int array1[6] = {1, 3, 4, 1, 5, 1};
    int array2[10] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
    int array3[0];
    int array4[1] = {1};
    int array5[2] = {1, 1};
    int array6[5] = {1, 2, 3, 4, 5};
    int array7[2] = {-1, 1};
    int array8[6] = {-1, -2, -3, 0, 1, 2};
    check(array1, 6, 3);
    check(array2, 10, 4);
    check(array3, 0, 0);
    check(array4, 1, 1);
    check(array5, 2, 1);
    check(array6, 5, 5);
    check(array7, 2, 2);
    check(array8, 6, 4);

    return EXIT_SUCCESS;
}
