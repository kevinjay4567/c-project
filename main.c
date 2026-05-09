#include "lexer.h"
#include <stdio.h>

int main(int argv, char* args[]) {

  if (argv == 1) {
    printf("File is required\n");
    return 1;
  }

  if (!read_file(args[1])) {
    return 1;
  }

  TokenKind pt = peek_next_token();


  printf("Token: %s | Type: %s | Loc: %d:%d,%d\n", pt.lexeme, token_type_to_str(pt.type), pt.loc.row, pt.loc.bgn, pt.loc.fwd);

  close_file();
  return 0;
}
