#include "pandemic.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>
/** This function is for checking if there is a comma in the line.
 * And if having, return the ptr of comma
 *@param line is the input line
 */
char *check_and_compute_comma_ptr(char *line)
{
  char *comma_ptr;
  // If line has no content, error happens.
  if (line == NULL)
  {
    fprintf(stderr, "Line has no content.\n");
    exit(EXIT_FAILURE);
  }

  // If the string does not contain a comma, error happens.
  // If it has a comma, return its pointer.
  if ((comma_ptr = strchr(line, ',')) == NULL)
  {
    fprintf(stderr, "The string has no comma.\n");
    exit(EXIT_FAILURE);
  }
  return comma_ptr;
}
/** This function is for computing the length of country name before comma.
 *@param str is the pattern string
 *@param size is the size of this whole string in case caught error out of bound
 */
size_t compute_name_len(char *str, size_t size)
{
  size_t len = 0;
  for (size_t i = 0; i < size; i++)
  {
    if (str[i] != ',')
    {
      len++;
    }
    else if (str[i] == ',')
    {
      break;
    }
  }
  return len;
}

/** This function is for parsing the input line into information of country's name and it's correspond population.
 *@param line is the input line
 */
country_t parseLine(char *line)
{
  // Initialize
  country_t countryInfo;
  countryInfo.name[0] = '\0';
  countryInfo.population = 0;
  char *comma_ptr;                                 // a pointer to the comma
  char *population_start_ptr, *population_end_ptr; // pointers intended to point the population's end and start

  size_t line_len; // size of the input line
  size_t name_len; // size of the country name in line

  // Find the comma or throw error
  comma_ptr = check_and_compute_comma_ptr(line);

  // Compute the length of the name of country
  line_len = strlen(line);
  name_len = compute_name_len(line, line_len);

  // Check the size of the country name
  if (name_len > MAX_NAME_LEN - 1)
  {
    fprintf(stderr, "The length of name is too large");
    exit(EXIT_FAILURE);
  }

  // Copy the name of country into return value
  for (size_t i = 0; i < name_len; i++)
  {
    countryInfo.name[i] = line[i];
  }
  countryInfo.name[name_len] = '\0'; // pay attention to ending with '\0'

  // Begin to handle the part after a comma
  population_start_ptr = comma_ptr + 1;
  population_end_ptr = comma_ptr + 1;

  // If there's no population, error happens
  if (*population_start_ptr == '\0' || *population_start_ptr == '\n')
  {
    fprintf(stderr, "There is no population.\n");
    exit(EXIT_FAILURE);
  }

  // If the remaining part has another or more comma(s), error happens
  if (strchr(population_start_ptr, ',') != NULL)
  {
    fprintf(stderr, "Too many commas!\n");
    exit(EXIT_FAILURE);
  }

  // If the population part has other character like '-', ' ', 'A', '&', error happens
  while (*population_end_ptr != '\n' && *population_end_ptr != '\0') // '\n' or '\0' is the end of the number.
  {
    if (!isdigit(*population_end_ptr))
    {
      fprintf(stderr, "number is invalid\n");
      exit(EXIT_FAILURE);
    }
    population_end_ptr += 1;
  }

  errno = 0; // To distinguish success/failure after call
  countryInfo.population = strtoul(population_start_ptr, NULL, 10);
  // Check if there is a number larger than ULONG_MAX
  if (errno == ERANGE)
  {
    fprintf(stderr, "strtoul failed due to the limite range of unsigned int.\n");
    exit(EXIT_FAILURE);
  }

  return countryInfo;
}

/** This function is for calculating the seven-day running average of case data.
 *@param data is an array of daily case data
 *@param n_days the number of days over which the data is measured
 *@param avg is result needed of the seven-day running average
 */
void calcRunningAvg(unsigned *data, size_t n_days, double *avg)
{
  if (data == NULL)
  {
    fprintf(stderr, "Data is NULL\n");
    exit(EXIT_FAILURE);
  }

  if (n_days < 7)
  {
    return;
  }

  for (size_t i = 0; i < n_days - 6; i++)
  {
    // Every loop will reset the total numver into 0
    double total = 0;
    avg[i] = 0;
    for (size_t date = i; date < i + 7; date++)
    {
      total += (double)data[date];
    }
    avg[i] = total / 7;
  }
  return;
}

/** This function is for calculating the cumulative number of cases that day per 100,000 people.
 *@param data is an array of daily case data
 *@param n_days the number of days over which the data is measured
 *@param pop is the population for certain country
 *@param cum is the cumulative number of cases that day per 100,000 people result needed
 */
void calcCumulative(unsigned *data, size_t n_days, uint64_t pop, double *cum)
{
  unsigned sum = 0; // Set it into double because of the opearation of division

  for (int i = 0; i < n_days; i++)
  {
    sum = sum + data[i];
    cum[i] = (sum / (double)pop) * 100000.0; // explict convert into double so that it can be divided correctly
  }
  return;
}

/** This function is for finding the maximum number of daily cases of all countries represented in the data
 *@param countries is the array of country's information
 *@param n_countries the length of param countries
 *@param data is a 2-D array of data, with each country's data representing a row
 *@param n_days the number of days over which the data is measured
 */
void printCountryWithMax(country_t *countries,
                         size_t n_countries,
                         unsigned **data,
                         size_t n_days)
{
  unsigned max_number = 0;
  size_t max_index = 0;
  for (size_t j = 0; j < n_days; j++)
  {
    for (size_t i = 0; i < n_countries; i++)
    {
      // Compute the max number and its correspond index
      if (data[i][j] > max_number)
      {
        max_number = data[i][j];
        max_index = i;
      }
    }
  }
  printf("%s has the most daily cases with %u\n", countries[max_index].name, max_number);
  return;
}
