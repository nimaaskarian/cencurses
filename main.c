#include <curses.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

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

#define CHARS_COUNT 2<<(sizeof(char)*7)
typedef struct {
  char * main_cmd;
  char * cmds[CHARS_COUNT];
} App;

void init_app(App * app)
{
  app->main_cmd = NULL;
  for (int i = 0; i < CHARS_COUNT; i++)
    app->cmds[i] = NULL;
}
void * handle_ch(void * arguments)
{
  App * app = (App *) arguments;
  while (1) {
    int ch = getch();
    switch (ch) {
      case 'q':
        curses_quit();
      break;
      default:
        {
          char * cmd = app->cmds[ch];
          if (cmd != NULL)  {
            popen(cmd, "r");
          }
        }
        break;
    }
  }
  pthread_exit(EXIT_SUCCESS);
}


void read_opts_to_app(int argc, char * argv[],App * app) {
  int ch;
  while ((ch = getopt(argc, argv, "m:c:")) != -1) {
    switch (ch) {
      case 'm':
        app->main_cmd = optarg;
      break;
      case 'c':
        {
          KeyCmd line;
          if (handle_line_to_keycmd(optarg, &line) == EXIT_FAILURE) {
            fprintf(stderr, "\"%s\" isnt a 'key' = 'value' pair.\n", optarg);
            curs_set(1);
            exit(EXIT_FAILURE);
          }
          app->cmds[(size_t)line.key] = line.cmd;
        }
      break;
    }
  }
}

int main(int argc, char *argv[])
{
  curses_init();
  App app;
  init_app(&app);

  pthread_t getch_thread;
  pthread_create(&getch_thread, NULL, handle_ch, &app);

  read_opts_to_app(argc, argv, &app);
  read_command_to_fn(app.main_cmd, center_curses_print_ascii);
  return EXIT_SUCCESS;
}
