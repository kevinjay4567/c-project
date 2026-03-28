#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#define BUFFER_LEN 4096

typedef enum { IDENTIFIER, KEYWORD, DIGIT, OPERATOR } TokenType;

int read_file(const char *path);
void close_file();
char *next_token();
#endif
