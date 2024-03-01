// vim:fileencoding=utf-8:foldmethod=marker
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ascii.h"
#include "position.h"
#include "utils.h"

// Variables {{{
const char * numbers[][FONTLEN] = {
{
"  ___  ",
" / _ \\ ",
"| | | |",
"| |_| |",
" \\___/ ",
},
 {
" _ ",
"/ |",
"| |",
"| |",
"|_|",
},
   
   {
" ____  ",
"|___ \\ ",
"  __) |",
" / __/ ",
"|_____|",
},
       
   {
" _____ ",
"|___ / ",
"  |_ \\ ",
" ___) |",
"|____/ ",
},
       
   {
" _  _   ",
"| || |  ",
"| || |_ ",
"|__   _|",
"   |_|  ",
},
        
   {
" ____  ",
"| ___| ",
"|___ \\ ",
" ___) |",
"|____/ ",
},
       
   {
"  __   ",
" / /_  ",
"| '_ \\ ",
"| (_) |",
" \\___/ ",
},
       
   {
" _____ ",
"|___  |",
"   / / ",
"  / /  ",
" /_/   ",
},
       
   {
"  ___  ",
" ( _ ) ",
" / _ \\ ",
"| (_) |",
" \\___/ ",
},
       
   {
"  ___  ",
" / _ \\ ",
"| (_) |",
" \\__, |",
"   /_/ ",
},
};

const char * space[FONTLEN] = {
  " ",
  " ",
  " ",
  " ",
  " ",
};

const char * colon[FONTLEN] = {
  "   ",
  " _ ",
  "(_)",
  " _ ",
  "(_)",
};
// }}}

const char ** resolve_ascii_ch(char ch) 
{
  if (isdigit(ch))
    return numbers[ch - '0'];

  switch (ch) {
    case ' ':
      return space;
    case ':':
      return colon;
  }

  return NULL;
}

inline void init_size(Position * size)
{
  *size = (Position){.x = 0, .y = 0};
}

void init_ascii(Ascii * ascii, size_t size)
{
  init_size(&ascii->size);
  ascii->buff = malloc(size*sizeof(char *));
  for (int i = 0; i < size; i++) {
    ascii->buff[i] = NULL;
  }
}

size_t append_to_ascii(const char ** append, char ** ascii)
{
  size_t max_size = 0;
  if (append == NULL) return max_size;

  for (int i = 0; i < FONTLEN; i++) {
    size_t size;
    if (ascii[i]) {
      size = asprintf(&ascii[i], "%s%s", ascii[i], append[i]);
    } else {
      size = asprintf(&ascii[i], "%s", append[i]);
    }

    if (size > max_size)
      max_size = size;
  }
  return max_size;
}

void append_line_to_ascii(const char * append, Ascii * ascii)
{
  if (append == NULL) return;
  size_t size = strlen(append);
  ascii->buff[ascii->size.y] = malloc(sizeof(char) * (size+1));
  strncpy(ascii->buff[ascii->size.y],append, size);
  ascii->buff[ascii->size.y][size] = '\0';
  ascii->size.y++;
}

Ascii resolve_ascii_str(char * line)
{
  Ascii output;
  init_ascii(&output, FONTLEN);

  output.size = (Position){.x = 0, .y = FONTLEN};

  for (unsigned int i = 0; line[i] != '\0'; i++){
    const char ** ascii_to_append = resolve_ascii_ch(line[i]);
    int line_size = append_to_ascii(ascii_to_append, output.buff);
    if (line_size > output.size.x)
      output.size.x = line_size;
  }
  output.buff[FONTLEN] = NULL;

  return output;
}

void ascii_increase_size(Ascii * ascii)
{
  char ** tmp = realloc(ascii->buff, (ascii->size.y+1)*sizeof(char *));
  ascii->buff = tmp;
}

Ascii resolve_ascii_str_cmd(char * line, const char * cmd)
{
  Ascii output;
  init_size(&output.size);
  output.buff = malloc(sizeof(char *));
  char * cmd_tmp;
  asprintf(&cmd_tmp, "%s %s", cmd, line);
  FILE * fp = popen(cmd_tmp, "r");
  ssize_t read;
  char * line_buff = NULL;
  size_t size = 0;

  while ((read = getline(&line_buff, &size, fp)) >= 0) {
    if (output.size.y) {
      ascii_increase_size(&output);
    }
    append_line_to_ascii(line_buff, &output);
    if (read > output.size.x)
      output.size.x = read;
  }
  fclose(fp);
  free(line_buff);

  return output;
}
