#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 4096

char buffer[2][BUFFER_LEN] = {0};
int current = 0;
char *lexeme_begin, *forward;

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

char next_char(FILE *in) {
  switch (*forward) {
  case '\0': {
    if (forward == &buffer[0][BUFFER_LEN - 1]) {
      size_t nb = fread(buffer[1], 1, BUFFER_LEN, in);
      buffer[1][nb] = '\0';
      forward = buffer[1];
    } else if (forward == &buffer[1][BUFFER_LEN - 1]) {
      size_t nb = fread(buffer[0], 1, BUFFER_LEN, in);
      buffer[0][nb] = '\0';
      forward = buffer[0];
    } else {
      return 0;
    }
  } break;
  case '/': {
    if (*(forward + 1) == '/') {
      while (*forward != '\n') {
        forward++;
      }
      forward++;
    } else {
      return 0;
    }
    break;
  }
  }

  return *forward;
}

char *next_token(FILE *in) {
  char *token;

  while (next_char(in)) {
    if (isspace(*forward)) {
      forward++;
      continue;
    }
    if (isalpha(*forward) || *forward == '_') {
      int idx = 0;
      token[idx] = *forward++;
      char nc = next_char(in);
      while (isalnum(nc) || nc == '_') {
        token[++idx] = *forward++;
        nc = next_char(in);
      }
      token[idx + 1] = '\0';
      forward--;
    } else if (*forward == '=') {
      int idx = 0;
      token[idx] = *forward++;
      char nc = next_char(in);
      if (nc == '=') {
        token[++idx] = *forward++;
        nc = next_char(in);
      }

      token[idx + 1] = '\0';
      forward--;
    } else if (isdigit(*forward)) {
      int idx = 0;
      while (isdigit(*forward)) {
        token[idx++] = *forward++;
      }

      token[idx] = '\0'; 
      forward--;
    } else if (*forward == '-') {
      int idx = 0;
      token[idx++] = *forward++;
      char nc = next_char(in);
      if (nc == '-' || nc == '=') {
        token[idx++] = nc;
      }

      token[idx] = '\0';
    } else if (*forward == ';') {
      token[0] = *forward;
      token[1] = '\0';
    }

    forward++;
    return token;
  }

  return 0;
}

int main() {
  FILE *in = fopen("input.txt", "r");
  if (!in)
    return 1;

  size_t n = fread(buffer[0], 1, BUFFER_LEN, in);

  if (n < BUFFER_LEN) {
    buffer[0][n] = '\0';
  }

  forward = buffer[0];
  lexeme_begin = forward;

  char *nt = next_token(in);
  while (nt) {
    printf("%s\n", nt);
    nt = next_token(in);
  }

  fclose(in);
  return 0;
}
