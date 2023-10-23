#include "TokenType.h"

#include <string.h>

const char *tt_str[] = {
  // Specials
  "UNEXPECTED_EOF", // 0
  "INVALID_TOKEN",  // 1
  "END_OF_FILE",    // 2

  // Symbols
  "SEMICOLON",      // 3
  "ASSIGN",         // 4

  // Logic operators
  "EQUAL",          // 5
  "NOT_EQUAL",      // 6
  "LOWER",          // 7
  "LOWER_EQUAL",    // 8
  "GREATER",        // 9
  "GREATER_EQUAL",  // 10

  // Arithmetic operators
  "ADD",            // 11
  "SUB",            // 12
  "MUL",            // 13
  "DIV",            // 14
  "MOD",            // 15
  "POW",            // 16

  // Keywords
  "PROGRAM",        // 17
  "WHILE",          // 18
  "DO",             // 19
  "DONE",           // 20
  "IF",             // 21
  "THEN",           // 22
  "ELSE",           // 23
  "OUTPUT",         // 24
  "TRUE",           // 25
  "FALSE",          // 26
  "READ",           // 27
  "NOT",            // 28

  // Others
  "NUMBER",         // 29
  "VAR"             // 30
};

const char* tt2str(enum TokenType type) {
  return tt_str[type + 2];
}
