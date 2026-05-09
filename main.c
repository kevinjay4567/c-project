#include "lexer.h"
#include <string.h>
#include <stdio.h>

int main(int argv, char* args[]) {
  if (argv == 1) {
    printf("File is required\n");
    return 1;
  }

  if (!read_file(args[1])) {
    return 1;
  }

  TokenKind ct = next_token();

  if (ct.type == KEYWORD && strcmp(ct.lexeme, "int") == 0) {
      if (peek_next_token().type == ID) {
          printf("GOOD\n");
      } else {
          printf("error: se espera un identificador despues de la palabra clave 'int'\n");
          printf("%s %s\n", ct.lexeme, peek_next_token().lexeme);
          printf("    ^\n");
      }
  }

  close_file();
  return 0;
}
