#ifndef NUMBERS_H_
#define NUMBERS_H_
#include <stdlib.h>
#define FONTLEN 5
char ** resolve_ascii_str(char * line, int * max_size);
extern const char * colon[FONTLEN];
extern const char * space[FONTLEN];
extern const char * numbers[][FONTLEN];
#endif // NUMBERS_H_
