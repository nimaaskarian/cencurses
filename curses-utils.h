#ifndef CURSES_UTILS_H_
#include <ncurses.h>
typedef struct {
  int y, x;
} Position;
void curses_init();
void curses_quit();
Position curses_center(Position str);
#endif // !CURSES_UTILS_H_