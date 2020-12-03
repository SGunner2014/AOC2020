#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"

struct policy_check {
  int min;
  int max;
  char chr;
  char *password;
};

void parse_line(char *line, struct policy_check **p_check)
{
  char *token;
  char *token2;
  char *policy;
  char *saveptr_inner;
  char *saveptr = (char *)malloc(sizeof(char) * strlen(line));
  char *saveptr_inner_2;

  memcpy(saveptr, line, strlen(line));

  token = strtok_r(saveptr, ":", &saveptr);
  if (token == NULL)
    return;

  saveptr_inner = token;

  // Get letter and policy
  // 1-3 a: asdasd
  policy = strtok_r(saveptr_inner, " ", &saveptr_inner);
  if (policy == NULL)
    return;

  saveptr_inner_2 = policy;
  token2 = strtok_r(saveptr_inner_2, "-", &saveptr_inner_2);
  if (token2 == NULL)
    return;

  (*p_check)->min = atoi(token2);

  token2 = strtok_r(saveptr_inner_2, "-", &saveptr_inner_2);
  if (token2 == NULL) {
    free(p_check);
    return;
  }

  (*p_check)->max = atoi(token2);

  token2 = strtok_r(saveptr_inner, " ", &saveptr_inner);
  if (token2 == NULL)
    return;

  (*p_check)->chr = token2[0];

  token2 = strtok_r(saveptr, ":", &saveptr);
  if (token2 == NULL)
    return;

  (*p_check)->password = ++token2; // Remove space from beginning
}

int main()
{
  FILE *fp = fopen(INPUT_FILE, "r");

  int i;
  size_t len;
  ssize_t nread;
  int counter = 0;
  char *line = NULL;
  int valid_passwords = 0;

  if (fp == NULL)
    exit(-1);

  struct policy_check *p_check =
      (struct policy_check *)calloc(1, sizeof(struct policy_check));

  while ((nread = getline(&line, &len, fp)) != -1) {
    printf("%s", line);
    parse_line(line, &p_check);

    if (strlen(line) <= 5)
      continue;

    i = 0;
    while (line[i] != '\0') {
      if (line[i] == p_check->chr) {
        counter++;
      }
      i++;
    }

    if (counter >= p_check->min && counter <= p_check->max) {
      valid_passwords++;
    }
  }

  printf("Valid passwords: %d\n", valid_passwords);

  fclose(fp);
  free(line);
  free(p_check);
}