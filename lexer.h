#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#define BUFFER_LEN 4096

typedef enum { LT, LE, EQ, AS, GT, GE, IF, ELSE, ID, NUMBER, KEYWORD, DIGIT, OP } TokenType;

typedef struct {
  int row;
  int col;
} TokenLoc;

typedef struct {
  TokenType type;
  TokenLoc loc;
  size_t lexeme_len;
  const char *lexeme;
} TokenKind;

int read_file(const char *path);
void close_file();
TokenKind next_token();
const char *token_type_to_str(TokenType t);
#endif
