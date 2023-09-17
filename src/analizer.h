#ifndef ANALIZER_H
#define ANALIZER_H

typedef enum { IDENTIFICATOR, NUMBER, OTHER } TokenType;

typedef struct {
  TokenType type;
  char *literal;
} Token;

void read_line(const char *line);

#endif
