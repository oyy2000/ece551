#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

kvpair_t parseKeyVals(char *line)
{
  kvpair_t kvPair;
  kvPair.key = NULL;
  kvPair.value = NULL;

  size_t keyLen = 0;
  while (*line != '=' && *line != '\0')
  {
    kvPair.key = realloc(kvPair.key, (keyLen + 1) * sizeof(kvPair.key));
    kvPair.key[keyLen] = *line;
    keyLen++;
    line++;
  }

  kvPair.key[keyLen] = '\0';

  line++;

  if (strchr(line, '\n') != NULL)
  {
    *strchr(line, '\n') = '\0';
  }

  kvPair.value = strdup(line);

  return kvPair;
}

kvarray_t *readKVs(const char *fname)
{
  FILE *f = fopen(fname, "r");
  if (f == NULL)
  {
    fprintf(stderr, "Failed to open file.");
    exit(EXIT_FAILURE);
  }
  kvarray_t *pairs = malloc(sizeof(*pairs));
  pairs->kvPairs = NULL;
  pairs->numPairs = 0;

  char *curr = NULL;
  size_t linecap;
  size_t numPairs = 0;

  while (getline(&curr, &linecap, f) >= 0)
  {
    pairs->kvPairs = realloc(pairs->kvPairs, (1 + numPairs) * sizeof(*pairs->kvPairs));
    pairs->kvPairs[numPairs] = parseKeyVals(curr);
    free(curr);
    curr = NULL;
    numPairs++;
  }

  free(curr);
  pairs->numPairs = numPairs;

  if (fclose(f) != 0)
  {
    fprintf(stderr, "Failed to close the input file!");
    exit(EXIT_FAILURE);
  }

  return pairs;
}

void freeKVs(kvarray_t *pairs)
{
  for (size_t i = 0; i < pairs->numPairs; i++)
  {
    free(pairs->kvPairs[i].key);
    free(pairs->kvPairs[i].value);
  }

  free(pairs->kvPairs);
  free(pairs);
}

void printKVs(kvarray_t *pairs)
{
  for (size_t i = 0; i < pairs->numPairs; i++)
  {
    printf("key = '%s' value = '%s'\n", pairs->kvPairs[i].key, pairs->kvPairs[i].value);
  }
}

char *lookupValue(kvarray_t *pairs, const char *key)
{
  char *value = NULL;
  for (size_t i = 0; i < pairs->numPairs; i++)
  {
    if (!strcmp(key, pairs->kvPairs[i].key))
    {
      value = pairs->kvPairs[i].value;
    }
  }
  return value;
}
