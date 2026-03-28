#include "lexer.h"
#include <stdio.h>

int main() {
  if (!read_file("input.txt")) {
    return 1;
  }

  char *nc = next_token();
  while (nc) {
    printf("Token: %s\n", nc);
    nc = next_token();
  }

  close_file();
  return 0;
}
