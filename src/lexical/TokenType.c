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

  // Keywords
  "PROGRAM",        // 16
  "WHILE",          // 17
  "DO",             // 18
  "DONE",           // 19
  "IF",             // 20
  "THEN",           // 21
  "ELSE",           // 22
  "OUTPUT",         // 23
  "TRUE",           // 24
  "FALSE",          // 25
  "READ",           // 26
  "NOT",            // 27

  // Others
  "NUMBER",         // 28
  "VAR"             // 29
};

const char* tt2str(enum TokenType type) {
  return tt_str[type + 2];
}
