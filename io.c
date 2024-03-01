#include <curses.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "io.h"

#define LENGTH 100
void read_command_to_fn(const char * cmd, void line_handler(char *))
{
  FILE* fp = popen(cmd, "r");

  if (fp == NULL) return;

  char buffer[LENGTH];
  while (fgets(buffer, LENGTH-1, fp)) {
    int count = strlen(buffer);

    buffer[count] = '\0';
    line_handler(buffer);
  }
  fclose(fp);
}

void read_one_time_command_to_fn(const char * cmd, void line_handler(char *))
{
  FILE* fp = popen(cmd, "r");

  if (fp == NULL) return;

  char buffer[LENGTH];
  fgets(buffer, LENGTH-1, fp);
  int count = strlen(buffer);

  buffer[count] = '\0';
  line_handler(buffer);

  fclose(fp);
}

char * trim_left(char * str)
{
  size_t offset = 0;

  while (str[offset] == ' ') {
    offset++;
  }
  return str + offset;
}

char * trim_right(char * str)
{
  size_t end = strlen(str);

  while (str[end-1] == ' ') {
    end--;
  }
  str[end] = '\0';
  return str;
}

int handle_line_to_keycmd(char * line, KeyCmd * output)
{
  line = trim_left(line);
  output->cmd = malloc(sizeof(char) * ARG_MAX);

  int count = sscanf(line, "'%c' = \"%[^\"]s'", &output->key, output->cmd);
  if (count == 2)
    return EXIT_SUCCESS;
  else 
    return EXIT_FAILURE;
}
