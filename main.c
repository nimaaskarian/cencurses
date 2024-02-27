#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "ascii.h"
#include "curses-utils.h"

void println(char * line) 
{
  int str_width;
  char ** ascii = resolve_ascii_str(line, &str_width);
  Position str_pos = {.x = str_width, .y = FONTLEN};
  Position mid_pos = curses_center(str_pos);

  unsigned int j = 0;

  clear();
  while (ascii[j] != NULL) {
    mvprintw(mid_pos.y+j,mid_pos.x, "%s\n", ascii[j]);
    j++;
  }
  refresh();
}

int main(int argc, char *argv[])
{
  curses_init();
  read_file_to_fn(stdin, println);
  return EXIT_SUCCESS;
}
