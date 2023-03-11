#include "pandemic.h"

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;
  char * start = line;
  char * end = line;
  //read the country name
  //skip characters until meet a comma
  while (*end != '\n' && *end != '\0' && *end != '\r' && *end != ',') {
    ++end;
  }
  //check if a comma is read
  if (*end != ',') {
    fprintf(
        stderr,
        "One line is empty or doesn't have a comma to separate the country name and its "
        "population!\n");
    exit(EXIT_FAILURE);
  }
  size_t i = 0;
  //read each character of the country name
  while (start != end) {
    //check whether country name has too many characters
    if (i == MAX_NAME_LEN - 1) {
      fprintf(stderr, "The name of a country is way too long! The length of the name must be less than %d!\n",MAX_NAME_LEN);
      exit(EXIT_FAILURE);
    }
    ans.name[i++] = *start;
    ++start;
  }
  //put a terminator at the end of the string
  ans.name[i] = '\0';
  //check whether the name of a country is read
  if (ans.name[0] == '\0') {
    fprintf(stderr, "A country doesn't have a name? I don't believe it.\n");
    exit(EXIT_FAILURE);
  }
  //read the country population
  ++end;
  //skip the front spaces and tabs
  while (*end == ' ' || *end == '\t') {
    ++end;
  }
  //check whether the population of a country is read
  if (*end == '\n' || *end == '\r' || *end == '\0') {
    fprintf(stderr, "A country doesn't have its population: %s!\n",ans.name);
    exit(EXIT_FAILURE);
  }
  //read each number of the country population
  while (*end != '\n' && *end != '\r' && *end != '\0') {
    //each character of country population should be a number
    if (*end < '0' || *end > '9') {
      fprintf(stderr,
              "One or both of the following errors occurred! Please fix it(them): %s!\n",ans.name);
      fprintf(stderr, "1. The name of the country should not include comma!\n");
      fprintf(stderr,
              "2. The population should be a pure integer that is non-negative!\n");
      exit(EXIT_FAILURE);
    }
    else {
      ans.population = ans.population * 10 + (*end - '0');
    }
    ++end;
  }
  //check whether the population is overflowed
  uint64_t num = ans.population;
  while (num != 0) {
    //compare the final result with the expected result
    if ((num % 10) != (*(--end) - '0')) {
      fprintf(stderr, "The population of a country is too large to handle: %s!\n",ans.name);
      exit(EXIT_FAILURE);
    }
    num /= 10;
  }
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  //check invalid inputs
  if (data == NULL || avg == NULL) {
    fprintf(stderr, "Invalid inputs, read and write arrays should not be null!\n");
    exit(EXIT_FAILURE);
  }
  //check the number of measured days is enough
  if (n_days < 7) {
    exit(EXIT_SUCCESS);
  }
  double sum = 0;
  unsigned * p = data;
  for (size_t i = 0; i < n_days; i++) {
    if (i < 6) {
      sum += (double)*(p++);
    }
    else if (i == 6) {
      sum += (double)*(p++);
      *(avg++) = sum / 7;
    }
    else {
      sum -= (double)*(data++);
      sum += (double)*(p++);
      *(avg++) = sum / 7;
    }
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  //check invalid inputs
  if (data == NULL || cum == NULL) {
    fprintf(stderr, "Invalid inputs, read and write arrays should not be null!\n");
    exit(EXIT_FAILURE);
  }
  //check the number of measured days is enough
  if (n_days == 0) {
    fprintf(stderr, "The number of measured days should not be zero: n_days!\n");
    exit(EXIT_FAILURE);
  }
  //check the number of population is enough
  if (pop == 0) {
    fprintf(stderr, "The population of a country should not be zero: pop!\n");
    exit(EXIT_FAILURE);
  }
  double sum_cases = 0;
  for (size_t i = 0; i < n_days; i++) {
    sum_cases += (double)*(data++);
    *(cum++) = (sum_cases / ((double)pop)) * 100000;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  //check invalid inputs
  if (data == NULL || countries == NULL) {
    fprintf(stderr, "Invalid inputs, two read arrays should not be null!\n");
    exit(EXIT_FAILURE);
  }
  //check the number of measured days is enough
  if (n_days == 0) {
    fprintf(stderr, "The number of measured days should not be zero: n_days!\n");
    exit(EXIT_FAILURE);
  }
  //check the number of countries is enough
  if (n_countries == 0) {
    fprintf(stderr, "The number of country should not be zero: n_countries!\n");
    exit(EXIT_FAILURE);
  }
  unsigned max_daily_cases = 0;
  size_t country_number = 0;
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      //find the maximum daily cases
      if (max_daily_cases < data[i][j]) {
        max_daily_cases = data[i][j];
        country_number = i;
      }
    }
  }
  printf("%s has the most daily cases with %u\n",
         countries[country_number].name,
         max_daily_cases);
}
