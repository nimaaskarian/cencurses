#include <stdlib.h>
#include <unistd.h>

#include "io.h"

#define LENGTH 100
void read_file_to_fn(FILE * file, void callback(char *))
{
  char buffer[LENGTH];
  int count;
  while ( (count = read(STDIN_FILENO, buffer, LENGTH-1)) ) {
    buffer[count] = '\0';
    callback(buffer);
  }
}
