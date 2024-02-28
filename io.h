// vim:fileencoding=utf-8:filetype=c
#ifndef IO_H_
#define IO_H_
#include <stdio.h>
void read_file_to_fn(FILE * file, void callback(char *));
#endif
