#include <stdlib.h>

#include "curses-utils.h"

void curses_initialize_screen()
{
  initscr();
  if (has_colors()) {
    // alacritty no opaque background
    use_default_colors();
    start_color();
    init_pair(1,COLOR_BLACK, COLOR_WHITE);
  }
  // fast key :D
  cbreak();

  // no cursor and no echo
  curs_set(0);
  noecho();
}

void curses_quit()
{
  endwin();
  exit(EXIT_SUCCESS);
}

void curses_center(size_t str_height, size_t str_width)
{

}
