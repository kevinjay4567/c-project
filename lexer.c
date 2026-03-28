#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *keywords[] = {"char", "int", "string"};

char buffer[2][BUFFER_LEN] = {0};
int current = 0;
char *lexeme_begin, *forward, token[64] = {0};
FILE *input = {0};

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
        forward++;
      }
    } else {
      return '\0';
    }
    break;
  }
  }

  return *forward++;
}

char *next_token() {
  while (*forward != '\0') {
    if (isspace(*forward)) {
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
    } else if (*forward == '=') {
      int idx = 0;
      token[idx] = next_char();
      if (*forward == '=') {
        token[++idx] = next_char();
      }
      token[idx + 1] = '\0';
    } else if (isdigit(*forward)) {
      int idx = 0;
      while (isdigit(*forward)) {
        token[idx++] = next_char();
      }

      token[idx] = '\0';
    } else if (*forward == '-') {
      int idx = 0;
      token[idx++] = next_char();
      if (*forward == '-' || *forward == '=') {
        token[idx++] = next_char();
      }

      token[idx] = '\0';
    } else if (*forward == ';') {
      token[0] = next_char();
      token[1] = '\0';
    }

    return token;
  };

  return 0;
}
