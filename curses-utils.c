#include <stdlib.h>

#include "curses-utils.h"

void curses_init()
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
  // non blocking getch
  nodelay(stdscr, FALSE);
}

void curses_quit()
{
  endwin();
  exit(EXIT_SUCCESS);
}

Position curses_center(Position str)
{
  int y, x;
  getmaxyx(stdscr, y, x);
  Position mid;
  mid.y = (y-str.y)/2;
  mid.x = (x-str.x)/2;

  return mid;
}
