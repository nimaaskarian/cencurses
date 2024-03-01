// vim:fileencoding=utf-8:filetype=c
#ifndef IO_H_
#define IO_H_
#include <stdio.h>
void read_command_to_fn(const char * cmd, void line_handler(char *));
void read_one_time_command_to_fn(const char * cmd, void line_handler(char *));
char * trim_left(char * str);
char * trim_right(char * str);
typedef struct {
  unsigned char key;
  char* cmd;
} KeyCmd;
int handle_line_to_keycmd(char * line, KeyCmd * output);
#endif
