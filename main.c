#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct TreeNode {
    char value[32];
    struct TreeNode *l_child;
    struct TreeNode *r_child;
} TreeNode;

int main(int argv, char* args[]) {
  if (argv == 1) {
    printf("File is required\n");
    return 1;
  }

  if (!read_file(args[1])) {
    return 1;
  }

  TokenKind ct = next_token();
  /*int count = 0;
  while (count < 5) {
      printf("%s\n", ct.lexeme);
      ct = next_token();
      count++;
      }*/

  ct = next_token();
  ct = next_token();
  ct = next_token();

  if (ct.type == KEYWORD && strcmp(ct.lexeme, "int") == 0) {
      if (peek_next_token().type == ID) {
          printf("GOOD\n");
      } else {
          printf("error: se espera un identificador despues de la palabra clave 'int'\n");
          printf("%s %s\n", ct.lexeme, peek_next_token().lexeme);
          printf("    ^\n");
      }
  }

  if (peek_next_token().type == OP && strcmp(peek_next_token().lexeme, "+") == 0) {
      TreeNode *n1 = malloc(sizeof(TreeNode));
      strcpy(n1->value, ct.lexeme);

      ct = next_token();
      ct = next_token();

      TreeNode *n2 = malloc(sizeof(TreeNode));
      strcpy(n2->value, ct.lexeme);

      TreeNode *add = malloc(sizeof(TreeNode));
      add->l_child = n1;
      add->r_child = n2;
      strcpy(add->value, "+");

      int number_l = atoi(add->l_child->value);
      int number_r = atoi(add->r_child->value);

      printf("%d %s %d = %d\n", number_l, add->value, number_r, number_l + number_r);
  }

  close_file();
  return 0;
}
