#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This function is used to figure out the ordering of the strings
// in qsort. You do not need to modify it.
int stringOrder(const void *vp1, const void *vp2)
{
  const char *const *p1 = vp1;
  const char *const *p2 = vp2;
  return strcmp(*p1, *p2);
}
// This function will sort data (whose length is count).
void sortData(char **data, size_t count)
{
  qsort(data, count, sizeof(char *), stringOrder);
}

void operation(FILE *f)
{
  char **lines = NULL;
  char *curr = NULL;
  size_t sz;
  size_t i = 0;

  while (getline(&curr, &sz, f) >= 0)
  {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }

  // post operations
  free(curr);
  sortData(lines, i);

  // print sorted data
  for (size_t j = 0; j < i; j++)
  {
    printf("%s", lines[j]);
    free(lines[j]);
  }
  free(lines);
}

int main(int argc, char **argv)
{
  if (argc == 1)
  {
    FILE *f = stdin;
    if (f == NULL)
    {
      fprintf(stderr, "Can not open the file!\n");
      return EXIT_FAILURE;
    }
    operation(f);
    if (fclose(f) != 0)
    {
      fprintf(stderr, "Failed to close the file!\n");
      return EXIT_FAILURE;
    }
  }
  else if (argc > 1)
  {
    for (int j = 1; j < argc; j++)
    {
      // open all the files and get lines of them
      FILE *f = fopen(argv[j], "r");
      if (f == NULL)
      {
        fprintf(stderr, "Can not open the file!\n");
        return EXIT_FAILURE;
      }
      operation(f);
      if (fclose(f) != 0)
      {
        fprintf(stderr, "Failed to close the file!\n");
        return EXIT_FAILURE;
      }
    }
  }

  return EXIT_SUCCESS;
}
