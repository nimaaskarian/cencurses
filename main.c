#include <curses.h>
#include <limits.h>
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

#define CHAR_COUNT 255
typedef struct {
  char * main_cont_cmd;
  char * main_cmd;
  char * config_path;
  char * cmds[CHAR_COUNT];
} App;

void init_app(App * app)
{
  app->main_cont_cmd = NULL;
  app->main_cmd = NULL;
  app->config_path = NULL;
  for (int i = 0; i < CHAR_COUNT; i++)
    app->cmds[i] = NULL;
}

void * handle_ch(void * arguments)
{
  App * app = (App *) arguments;
  while (1) {
    int ch = getch();
    switch (ch) {
      case 'q':
        curses_quit(EXIT_SUCCESS);
        if (app->main_cmd) {
          read_one_time_command_to_fn(app->main_cmd, center_curses_print_ascii);
        }
      break;
      default:
        {
          char * cmd = app->cmds[ch%CHAR_COUNT];
          if (cmd != NULL)  {
            popen(cmd, "r");
            if (app->main_cmd) {
              read_one_time_command_to_fn(app->main_cmd, center_curses_print_ascii);
            }
          }
        }
        break;
    }
  }
  pthread_exit(EXIT_SUCCESS);
}

inline void app_add_line_cmd(App * app, char * line)
{
  KeyCmd cmd;
  if (handle_line_to_keycmd(line, &cmd) == EXIT_FAILURE) {
    fprintf(stderr, "\"%s\" isnt a 'key' = 'value' pair.\n", line);
    curs_set(1);
    exit(EXIT_FAILURE);
  }
  app->cmds[cmd.key%CHAR_COUNT] = cmd.cmd;
}

void read_config_file_to_app(App * app)
{
  FILE * fp = fopen(app->config_path, "r");
  if (!fp)
    return;

  ssize_t read;
  char * line = NULL;
  size_t size = 0;
  while ((read = getline(&line, &size, fp)) >= 0) {
    app_add_line_cmd(app, line);
  }

  if (line)
    free(line);
  fclose(fp);
}

void read_opts_to_app(int argc, char * argv[],App * app) {
  int ch;
  while ((ch = getopt(argc, argv, "M:c:m:")) != -1) {
    switch (ch) {
      case 'M':
        app->main_cont_cmd = optarg;
      break;
      case 'm':
        app->main_cmd = optarg;
      break;
      case 'c':
        app_add_line_cmd(app, optarg);
      break;
    }
  }
}

void update_config_path(App * app)
{
  if (app->config_path == NULL) {
    char * home = getenv("HOME");
    asprintf(&app->config_path, "%s/.config/numcursesrc", home);
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
  update_config_path(&app);
  read_config_file_to_app(&app);

  if (app.main_cont_cmd) {
    read_command_to_fn(app.main_cont_cmd, center_curses_print_ascii);
  }
  else if (app.main_cmd) {
    while (true) {
      read_one_time_command_to_fn(app.main_cmd, center_curses_print_ascii);
      sleep(1);
    }
  }
  else {
    fputs("Use either -m or -M arguments to give me a command.", stderr);
    curses_quit(EXIT_FAILURE);
  }

  curses_quit(EXIT_SUCCESS);
}
