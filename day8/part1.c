#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"

struct Instruction {
  int line_no;
  struct Instruction *next;
};

void execute_instruction(char *instruction, int *accumulator,
                         int *instruction_pointer)
{

  if (strncmp(instruction, "acc", 3) == 0) {
    if (strstr(instruction, "-")) {
      (*accumulator) -= atoi(instruction + 5);
    } else {
      (*accumulator) += atoi(instruction + 5);
    }

    (*instruction_pointer)++;
  } else if (strncmp(instruction, "jmp", 3) == 0) {
    if (strstr(instruction, "-")) {
      (*instruction_pointer) -= atoi(instruction + 5);
    } else {
      (*instruction_pointer) += atoi(instruction + 5);
    }
  } else {
    (*instruction_pointer)++;
  }
}

int execute_program(char program[1024][256])
{
  int accumulator = 0;
  int instruction_pointer = 0;
  int old_instruction_pointer;

  while (strcmp(program[instruction_pointer], "\0") &&
         instruction_pointer <= 1024) {
    old_instruction_pointer = instruction_pointer;
    execute_instruction(program[instruction_pointer], &accumulator,
                        &instruction_pointer);
    strcpy(program[old_instruction_pointer], "\0");

    printf("Executed instruction (acc: %d) `%d`: %s\n", accumulator,
           instruction_pointer, program[instruction_pointer]);
  }

  return accumulator;
}

int main()
{
  FILE *fp = fopen(INPUT_FILE, "r");

  int accumulator = 0;
  char buffer[1024][256];
  int instruction_pointer = 0;

  char *line;
  ssize_t nread;
  size_t len = 0;
  int counter = 0;

  while ((nread = getline(&line, &len, fp)) != -1) {
    strcpy(buffer[counter], line);
    counter++;
  }

  printf("Program result: %d", execute_program(buffer));

  fclose(fp);
  free(line);
}