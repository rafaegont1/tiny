#ifndef SYNTATIC_ANALYSIS_H
#define SYNTATIC_ANALYSIS_H

#include "../lexical/LexicalAnalysis.h"
#include "../interpreter/command/command.h"

typedef struct SyntaticAnalysis SyntaticAnalysis;

struct SyntaticAnalysis {
  LexicalAnalysis *la;
  Lexeme lex;
};

void sa_init(SyntaticAnalysis* sa, LexicalAnalysis* lex);
BlockCmd* sa_start(SyntaticAnalysis* sa);

#endif /* SYNTATIC_ANALYSIS_H */
