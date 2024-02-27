#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "ascii.h"

void println(char * line) 
{
  char ** ascii = resolve_ascii_str(line);
  fflush(stdout);

  unsigned int j = 0;

  while (ascii[j] != NULL) {
    printf("%s\n", ascii[j++]);
  }
}

int main(int argc, char *argv[])
{
  read_file_to_fn(stdin, println);
  return EXIT_SUCCESS;
}
