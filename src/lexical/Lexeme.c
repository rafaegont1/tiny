#include "Lexeme.h"

#include <stdio.h>
#include <stdlib.h>

void lx_init(Lexeme* lex) {
  lex->token[0] = '\0';
  //lex->token_sz = 0;
  lex->type = TT_END_OF_FILE;
}
