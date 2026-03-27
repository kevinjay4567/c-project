#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 4096

// TODO: Aun no se utiliza
typedef enum {
  LT = '<',
  EQ = '=',
} Tokens;

// TODO: Aun no se utiliza
typedef struct {
  Tokens token;
  char name[8];
} Symbol;

// TODO: Se puede mejorar?
typedef struct {
  size_t length;
  char name[];
} Identifier;

char *keywords[] = {"char", "int", "string"};

int is_alund(char c) { return isalpha(c) || c == '_'; }

int kw_contain(char *keywords[], size_t length, char *search) {
  for (int i = 0; i < length; i++) {
    if (strcmp(keywords[i], search) == 0) {
      return 1;
    }
  }

  return 0;
}

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

// TODO: Se hace lo mismo muchas veces
void tokenizer(char *s) {
  size_t len = strlen(s);
  char lexeme[36] = {0};
  int phase = 0;

  Identifier *id = malloc(sizeof(Identifier) + 1024);

  for (int i = 0; i < len; i++) {

    if (phase == 0) {
      if (isalpha(s[i]) || s[i] == '_') {
        lexeme[strlen(lexeme)] = s[i];
        lexeme[strlen(lexeme) + 1] = '\0';
      } else if (s[i] == ';') {
        lexeme[strlen(lexeme)] = s[i];
        lexeme[strlen(lexeme) + 1] = '\0';
      } else if (isdigit(s[i])) {
        lexeme[strlen(lexeme)] = s[i];
        lexeme[strlen(lexeme) + 1] = '\0';
      } else {
        op_automate(s[i], phase);
      }
    } else {
      if ((isalpha(s[i - 1]) || s[i - 1] == '_') &&
          (isalnum(s[i]) || s[i] == '_')) {
        lexeme[strlen(lexeme)] = s[i];
        lexeme[strlen(lexeme) + 1] = '\0';
      } else if (isdigit(s[i - 1]) && isdigit(s[i])) {
        lexeme[strlen(lexeme)] = s[i];
        lexeme[strlen(lexeme) + 1] = '\0';
      } else if (s[i] == ';') {
        lexeme[strlen(lexeme)] = s[i];
        lexeme[strlen(lexeme) + 1] = '\0';
      } else {
        op_automate(s[i], phase);
      }
    }

    phase++;
  }

  if (kw_contain(keywords, sizeof(keywords) / sizeof(keywords[0]), lexeme)) {
    printf("Lexeme: %s | Type: keyword\n", lexeme);
  } else {
    if (isalpha(lexeme[0]) || lexeme[0] == '_') {
      strcpy(id->name, lexeme);
      id->length = strlen(id->name);
      printf("Lexeme: %s | Type: id\n", id->name);
    } else if (isdigit(lexeme[0])) {
      printf("Lexeme: %d | Type: digit\n", atoi(lexeme));
    } else if (lexeme[0] == ';') {
      printf("Lexeme: %s | Type: semi\n", lexeme);
    }
  }

  free(id);
}

int main() {
  FILE *in = fopen("input.txt", "r");
  if (!in)
    return 1;

  char buffer[BUFFER_LEN];
  char s_buffer[BUFFER_LEN];
  char *forward;

  while (fgets(buffer, sizeof(buffer), in)) {
    forward = buffer;
    char token[128];
    while (forward != &buffer[strlen(buffer)]) {
      if (!isspace(*forward)) {
        if (*forward == ';') {
          if (strlen(token) > 0) {
            tokenizer(token);
          }

          token[0] = *forward;
          token[1] = '\0';
          tokenizer(token);
          token[0] = '\0';
        } else {
          size_t len = strlen(token);
          token[len] = *forward;
          token[len + 1] = '\0';
        }
      } else {
        if (strlen(token) > 0) {
          tokenizer(token);
        }

        token[0] = '\0';
      }

      switch (*forward++) {
      case '\0':
        if (forward == &buffer[BUFFER_LEN - 1]) {
          printf("Final del primer buffer");
        } else if (forward == &s_buffer[BUFFER_LEN - 1]) {
          printf("Final del segundo buffer");
        } else {
          printf("Final de la linea");
          break;
        }
      }
    }
  }

  fclose(in);
  return 0;
}
