#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 4096

typedef enum {
  LT = '<',
  EQ = '=',
} Tokens;

typedef struct {
  Tokens token;
  char name[8];
} Symbol;

void op_automate(char l, int phase) {
  if (phase == 0) {
    switch (l) {
    case '<':
      printf("Lexeme: %c | Type: operand\n", l);
      break;
    case '>':
      printf("Lexeme: %c | Type: operand\n", l);
      break;
    case '+':
      printf("Lexeme: %c | Type: operand\n", l);
      break;
    case '-':
      printf("Lexeme: %c | Type: operand\n", l);
      break;
    case '=':
      printf("Lexeme: %c | Type: operand\n", l);
      break;
    case '*':
      printf("Lexeme: %c | Type: operand\n", l);
      break;
    }
  } else if (phase == 1) {
    switch (l) {
    case '=':
      printf("Lexeme: %c | Type: operand\n", l);
      break;
    default:
      printf("Incorrect Operand\n");
    }
  } else {
    printf("Incorrect Operand\n");
  }
}

void tokenizer(char *s) {
  size_t len = strlen(s);
  char lexeme[36] = {0};
  int phase = 0;

  for (int i = 0; i < len; i++) {

    if (phase == 0) {
      if (isalpha(s[i]) || s[i] == '_') {
        lexeme[strlen(lexeme)] = s[i];
        lexeme[strlen(lexeme) + 1] = '\0';
      } else if (s[i] == ';') {
        lexeme[strlen(lexeme)] = s[i];
        lexeme[strlen(lexeme) + 1] = '\0';
      } else {
        op_automate(s[i], phase);
      }
    } else {
      if (isalnum(s[i]) || s[i] == '_') {
        lexeme[strlen(lexeme)] = s[i];
        lexeme[strlen(lexeme) + 1] = '\0';
      } else if (s[i] == ';') {
        lexeme[strlen(lexeme)] = s[i];
        lexeme[strlen(lexeme) + 1] = '\0';
      } else {
        op_automate(s[i], phase);
      }
    }

    phase ++;
  }

  if (strcmp(lexeme, "int") == 0) {
    printf("Lexeme: %s | Type: keyword\n", lexeme);
  } else {
    printf("Lexeme: %s | Type: regular\n", lexeme);
  }
}

int main() {
  FILE *in = fopen("input.txt", "r");
  int begin = 0, forward = 0, phase = 0;
  char buffer[BUFFER_LEN];
  char s_buffer[BUFFER_LEN];
  buffer[sizeof(buffer) - 1] = EOF;
  s_buffer[sizeof(s_buffer) - 1] = EOF;
  Symbol sym = {0};

  while (fgets(buffer, sizeof(buffer), in)) {
    size_t length = strlen(buffer);
    char token[128] = {0};

    while (forward < length) {
      char c_char = buffer[forward];
      if (!isspace(c_char)) {
        size_t len = strlen(token);
        token[len] = c_char;
        token[len + 1] = '\0';
      } else {
        if (strlen(token) > 0) {
          tokenizer(token);
        }
        token[0] = '\0';
      }
      forward++;
    }

    forward = 0;
  }

  fclose(in);
  return 0;
}
