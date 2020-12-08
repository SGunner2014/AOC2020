#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"

int in_array(const char *array[], int length, const char *str)
{
  int i;
  for (i = 0; i < length; i++) {
    if (strcmp(array[i], str) == 0) {
      return 1;
    } else {
      printf("str: %s, cmp: %s\n", str, array[i]);
    }
  }

  return 0;
}

// Fills in the values from the current line
int parse_values(char *line)
{
  const char *required_fields[] = {"byr", "iyr", "eyr", "hgt",
                                   "hcl", "ecl", "pid"};

  int values_found = 0;
  char *field = (char *)malloc(3 * sizeof(char));
  // char *value = (char *)malloc(256 * sizeof(char));

  char *token = strtok(line, " ");
  while (token != NULL) {
    printf("token: %s\n", token);
    strncpy(field, token, 3);
    if (in_array(required_fields, 7, field)) {
      values_found++;
    }
    // strcpy(value, token + 4);
    token = strtok(NULL, " ");
  }

  free(field);
  // free(value);

  return values_found;
}

int main()
{
  FILE *fp = fopen(INPUT_FILE, "r");
  if (fp == NULL)
    exit(-1);

  ssize_t nread;
  size_t len = 0;
  char *line = NULL;
  int successful = 0;
  int is_new_passport = 1;
  int remaining_values = 7;

  while ((nread = getline(&line, &len, fp)) != -1) {
    if (is_new_passport) {
      // Validate the old passport and create a new one
      if (remaining_values == 0) {
        successful++;
      }
      remaining_values = 7;
      is_new_passport = 0;
    }

    // If we encounter an empty line, it's a fresh passport
    if (strcmp(line, "\n") == 0) {
      is_new_passport = 1;
      continue;
    } else {
      printf("line: %s\n", line);
    }

    remaining_values -= parse_values(line);
  }

  printf("Successful passports: %d\n", successful);

  fclose(fp);
  free(line);
}