#ifndef LEXICAL_ANALYSIS_H
#define LEXICAL_ANALYSIS_H

#include <stdio.h>
#include "Lexeme.h"
#include "SymbolTable.h"

typedef struct LexicalAnalysis LexicalAnalysis;

struct LexicalAnalysis {
  int line;
  map_int_t symbol_table;
  FILE* input;
};

void la_init(LexicalAnalysis* la, const char* filename);
void la_deinit(LexicalAnalysis* la);
Lexeme la_nextToken(LexicalAnalysis* la);

#endif
