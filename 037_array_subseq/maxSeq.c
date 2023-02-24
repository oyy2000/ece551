#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int *array, size_t n)
{
    size_t answer = 0;
    size_t counter = 1;
    if (n <= 0)
    {
        return answer;
    }
    else
    {
        for (size_t i = 1; i < n; i++)
        {
            if (array[i] > array[i - 1])
            {
                counter++;
            }
            else
            {
                if (answer < counter)
                {
                    answer = counter;
                }
                counter = 1;
            }
        }
        if (answer < counter)
        {
            answer = counter;
        }
    }
    return answer;
}