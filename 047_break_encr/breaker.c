#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int findEIndex(int array[], int n)
{
    int eIndex = 0;
    int i;

    for (i = 0; i < n; i++)
    {
        if (array[i] > array[eIndex])
        {
            eIndex = i;
        }
    }
    return eIndex;
}

int getkey(FILE *f)
{
    int frequency[26] = {0};
    int ch;
    int eIndex;

    // count the frequency of characters
    while ((ch = fgetc(f)) != EOF)
    {
        if (isalpha(ch))
        {
            frequency[tolower(ch) - 'a']++;
        }
    }
    eIndex = findEIndex(frequency, 26);

    return (eIndex + 22) % 26;
}

int main(int argc, char **argv)
{
    FILE *f;
    int key;

    if (argc != 2)
    {
        fprintf(stderr, "usage %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    f = fopen(argv[1], "r");

    key = getkey(f);
    printf("%d\n", key);

    fclose(f);
    return 0;
}