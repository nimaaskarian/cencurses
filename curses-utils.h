// vim:fileencoding=utf-8:filetype=c
#ifndef CURSES_UTILS_H_
#define CURSES_UTILS_H_
#include <ncurses.h>
#include "position.h"
void curses_init();
void curses_quit();
Position curses_center(Position str);
#endif // !CURSES_UTILS_H_
