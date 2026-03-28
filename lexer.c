#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *keywords[] = {"char", "int", "string"};

char buffer[2][BUFFER_LEN] = {0};
int current = 0, cur_col = 1, cur_row = 1;
char *lexeme_begin, *forward, token[64] = {0};
FILE *input = {0};

const char *token_type_to_str(TokenType t) {
  switch (t) {
  case LT:
    return "LT";
  case LE:
    return "LE";
  case EQ:
    return "EQ";
  case AS:
    return "AS";
  case GT:
    return "GT";
  case ID:
    return "ID";
  case KEYWORD:
    return "KEYWORD";
  case DIGIT:
    return "DIGIT";
  case OP:
    return "OP";
  case SEMI:
    return "SEMI";
  default:
    return "UNKNOWN";
  }
}

int read_file(const char *path) {
  input = fopen(path, "r");

  if (!input) {
    return 0;
  }

  size_t n = fread(buffer[0], 1, BUFFER_LEN, input);

  if (n < BUFFER_LEN) {
    buffer[0][n] = '\0';
  }

  forward = buffer[0];
  lexeme_begin = forward;

  return 1;
}

void close_file() { fclose(input); }

char peek_next_char() {
  if (*forward == '\0') {
    return '\0';
  }

  return *(forward + 1);
}

char next_char() {
  switch (*forward) {
  case '\0': {
    if (forward == &buffer[0][BUFFER_LEN - 1]) {
      size_t nb = fread(buffer[1], 1, BUFFER_LEN, input);
      buffer[1][nb] = '\0';
      forward = buffer[1];
    } else if (forward == &buffer[1][BUFFER_LEN - 1]) {
      size_t nb = fread(buffer[0], 1, BUFFER_LEN, input);
      buffer[0][nb] = '\0';
      forward = buffer[0];
    } else {
      return '\0';
    }
  } break;
  case '/': {
    if (*(forward + 1) == '/') {
      while (*forward != '\n') {
        cur_col++;
        forward++;
      }
      return *forward;
    } else {
      return '\0';
    }
    break;
  }
  }

  cur_col++;
  return *forward++;
}

TokenKind next_token() {
  TokenType t_token = {-1};
  while (*forward != '\0') {
    if (isspace(*forward) || *forward == '\t' || *forward == '\n') {
      if (*forward == '\n') {
        cur_row++;
        cur_col = 0;
      }
      next_char();
      continue;
    }

    if (*forward == '/') {
      next_char();
      continue;
    }

    if (isalpha(*forward) || *forward == '_') {
      int idx = 0;
      token[idx] = next_char();
      while (isalnum(*forward) || *forward == '_') {
        token[++idx] = next_char();
      }

      token[idx + 1] = '\0';
      if (strcmp(token, "int") == 0) {
        t_token = KEYWORD;
      } else {
        t_token = ID;
      }
    } else if (*forward == '=') {
      int idx = 0;
      token[idx] = next_char();
      if (*forward == '=') {
        token[++idx] = next_char();
        t_token = AS;
      } else {
        t_token = EQ;
      }

      token[idx + 1] = '\0';
    } else if (isdigit(*forward)) {
      int idx = 0;
      while (isdigit(*forward)) {
        token[idx++] = next_char();
      }

      t_token = DIGIT;
      token[idx] = '\0';
    } else if (*forward == '-') {
      int idx = 0;
      token[idx++] = next_char();
      if (*forward == '-' || *forward == '=') {
        token[idx++] = next_char();
      } else {
        t_token = OP;
      }

      token[idx] = '\0';
    } else if (*forward == ';') {
      token[0] = next_char();
      token[1] = '\0';
      t_token = SEMI;
    }

    //FIXME: Solucionar el cursor de columna final esta movido 1 posicion a la derecha
    size_t len = strlen(token);
    return (TokenKind){.type = t_token,
                       .loc = {.row = cur_row, .fwd = cur_col, .bgn = (cur_col - len)},
                       .lexeme = token,
                       .lexeme_len = strlen(token)};
  };

  return (TokenKind){0};
}
