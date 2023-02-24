#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void printRotate(char matrix[][10])
{
    for (int j = 0; j < 10; j++)
    {
        for (int i = 9; i >= 0; i--)
        {
            fprintf(stdout, "%c", matrix[i][j]);
        }
        fprintf(stdout, "\n");
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Need one and only one input file!\n");
        return EXIT_FAILURE;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        fprintf(stderr, "Can not open the file!\n");
        return EXIT_FAILURE;
    }
    char matrix[10][10] = {0};
    char c = ' ';
    int column = 0, row = 0;
    while ((c = fgetc(f)) != EOF)
    {
        if (c != '\n')
        {
            if (column > 9 || row > 9)
            {
                fprintf(stderr, "Invalid matrix\n");
                exit(EXIT_FAILURE);
            }
            else
            {
                if (c < 0 || c > 255)
                {
                    fprintf(stderr, "Invalid character\n");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    matrix[row][column] = c;
                    column++;
                }
            }
        }
        else
        {
            column = 0;
            row++;
        }
    }
    if (row != 10 || column != 0)
    {
        fprintf(stderr, "Invalid matrix\n");
        exit(EXIT_FAILURE);
    }
    printRotate(matrix);

    if (fclose(f) != 0)
    {
        fprintf(stderr, "Failed to close the file!\n");
        return EXIT_FAILURE;
    }
}