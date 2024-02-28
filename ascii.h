// vim:fileencoding=utf-8:filetype=c
#ifndef NUMBERS_H_
#define NUMBERS_H_
#include <stdlib.h>

#include "position.h"

#define FONTLEN 5
typedef struct {
  char ** buff;
  Position size;
} Ascii;
Ascii resolve_ascii_str(char * line);
extern const char * colon[FONTLEN];
extern const char * space[FONTLEN];
extern const char * numbers[][FONTLEN];
#endif // NUMBERS_H_
