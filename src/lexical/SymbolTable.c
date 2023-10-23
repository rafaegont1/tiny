#include "SymbolTable.h"

void st_init(map_int_t* symbol_table) {
  map_init(symbol_table);

  // Symbols
  map_set(symbol_table, ";", TT_SEMICOLON);
  map_set(symbol_table, "=", TT_ASSIGN);

  // Logic operators
  map_set(symbol_table, "==", TT_EQUAL);
  map_set(symbol_table, "!=", TT_NOT_EQUAL);
  map_set(symbol_table, "<", TT_LOWER);
  map_set(symbol_table, "<=", TT_LOWER_EQUAL);
  map_set(symbol_table, ">", TT_GREATER);
  map_set(symbol_table, ">=", TT_GREATER_EQUAL);

  // Arithmetic operators
  map_set(symbol_table, "+", TT_ADD);
  map_set(symbol_table, "-", TT_SUB);
  map_set(symbol_table, "*", TT_MUL);
  map_set(symbol_table, "/", TT_DIV);
  map_set(symbol_table, "%", TT_MOD);
  map_set(symbol_table, "^", TT_POW);

  // Keywords
  map_set(symbol_table, "program", TT_PROGRAM);
  map_set(symbol_table, "while", TT_WHILE);
  map_set(symbol_table, "do", TT_DO);
  map_set(symbol_table, "done", TT_DONE);
  map_set(symbol_table, "if", TT_IF);
  map_set(symbol_table, "then", TT_THEN);
  map_set(symbol_table, "else", TT_ELSE);
  map_set(symbol_table, "output", TT_OUTPUT);
  map_set(symbol_table, "true", TT_TRUE);
  map_set(symbol_table, "false", TT_FALSE);
  map_set(symbol_table, "read", TT_READ);
  map_set(symbol_table, "not", TT_NOT);
}

bool st_contains(map_int_t* symbol_table, const char* token) {
  return map_get(symbol_table, token) != NULL;
}

enum TokenType st_find(map_int_t* symbol_table, const char* token) {
  int *token_type = map_get(symbol_table, token);

  return token_type != NULL ? *token_type : TT_VAR;
}
