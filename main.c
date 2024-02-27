#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "io.h"
#include "ascii.h"
#include "curses-utils.h"

void center_curses_print_ascii(char * line) 
{
  Ascii ascii = resolve_ascii_str(line);
  Position mid_pos = curses_center(ascii.size);

  clear();
  for (int j = 0; ascii.buff[j] != NULL; j++) {
    mvprintw(mid_pos.y+j,mid_pos.x, "%s\n", ascii.buff[j]);
  }
  refresh();
}


int main(int argc, char *argv[])
{
  curses_init();
  read_file_to_fn(stdin, center_curses_print_ascii);
  return EXIT_SUCCESS;
}
