#ifndef ANALIZER_H
#define ANALIZER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum { IDENTIFICATOR, NUMBER, OTHER } TokenType;

typedef struct {
  TokenType type;
  char *literal;
} Token;

void read_line(const char *line);

#endif
