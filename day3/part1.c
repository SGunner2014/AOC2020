#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"

int detect_collisions(char map[323][256], int down_travel, int right_travel)
{
  int counter, position, collisions;
  counter = position = collisions = 0;

  // Check how many collisions we get
  for (counter = 0; counter < 323; counter += down_travel) {
    if (map[counter][position] == '#') {
      collisions++;
    }

    position = (position + right_travel) % (strlen(map[counter]) - 1);
  }

  return collisions;
}

int main()
{
  char *line;
  ssize_t nread;
  size_t len = 0;
  int counter = 0;
  char map[323][256];
  int down_travels[] = {1, 1, 1, 1, 2};
  int right_travels[] = {1, 3, 5, 7, 1};
  int collisions = 0;

  FILE *fp = fopen(INPUT_FILE, "r");

  // Read in the lines
  while ((nread = getline(&line, &len, fp)) != -1) {
    strcpy(map[counter], line);
    counter++;
  }

  int i;
  for (i = 0; i < 5; i++) {
    if (collisions == 0)
      collisions = detect_collisions(map, down_travels[i], right_travels[i]);
    else
      collisions *= detect_collisions(map, down_travels[i], right_travels[i]);
  }

  printf("Collisions: %d\n", collisions);

  free(line);
  fclose(fp);
}