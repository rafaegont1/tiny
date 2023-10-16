#ifndef LEXEME_H
#define LEXEME_H

#include "TokenType.h"

#define TOKEN_SZ 64

typedef struct Lexeme {
  char token[TOKEN_SZ];
  enum TokenType type;
} Lexeme;

void lx_init(Lexeme* lex);

#endif /* LEXEME_H */
