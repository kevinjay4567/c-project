#include "analizer.h"
#include <ctype.h>
#include <stdio.h>

_Bool is_letter(char c) { return isalpha(c) != 0; }
_Bool is_digite(char c) { return isdigit(c) != 0; }

void read_line(const char *line) {

  int i = 0;
  while (line[i] != '\0') {
    char c = line[i];

    char lexeme[100];
    int j = 0;

    if (isspace(c)) {
      i++;
      continue;
    }

    if (is_letter(c) || c == '_') {
      lexeme[j++] = c;
      i++;

      while (is_letter(line[i]) || is_digite(line[i]) || line[i] == '_') {
        lexeme[j++] = line[i];
        i++;
      }
      lexeme[j] = '\0';
      printf("Token: %s\n", lexeme);
    } else if (is_digite(c)) {
      lexeme[j++] = c;
      i++;
      while (is_digite(line[i])) {
        lexeme[j++] = line[i];
        i++;
      }
      lexeme[j] = '\0';
      printf("Token: %s (Type: Number)\n", lexeme);

    } else {
      i++;
    }
  }
}
