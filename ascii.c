// vim:fileencoding=utf-8:foldmethod=marker
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ascii.h"
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

void init_ascii(Ascii * ascii)
{
  ascii->size = (Position){.x = 0, .y = 0};
  ascii->buff = malloc((FONTLEN+1)*sizeof(char *));
  for (int i = 0; i < FONTLEN; i++) {
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

Ascii resolve_ascii_str(char * line)
{
  Ascii output;
  init_ascii(&output);

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
