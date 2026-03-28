#include "lexer.h"
#include <stdio.h>

int main() {
  if (!read_file("input.txt")) {
    return 1;
  }

  TokenKind nc = next_token();

  while (nc.lexeme) {
      printf("Token: %s | Type: %s\n", nc.lexeme, token_type_to_str(nc.type));
    nc = next_token();
  }

  close_file();
  return 0;
}
