#include "lexer.h"
#include <stdio.h>

int main() {
  if (!read_file("input.txt")) {
    return 1;
  }

  TokenKind nc = next_token();

  while (nc.lexeme) {
      printf("Token: %s | Type: %s | Loc: %d:%d,%d\n", nc.lexeme, token_type_to_str(nc.type), nc.loc.row, nc.loc.bgn, nc.loc.fwd);
    nc = next_token();
  }

  close_file();
  return 0;
}
