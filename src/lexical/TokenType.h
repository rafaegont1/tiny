#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

enum TokenType {
  // Specials
  TT_UNEXPECTED_EOF = -2,
  TT_INVALID_TOKEN  = -1,
  TT_END_OF_FILE    =  0,

  // Symbols
  TT_SEMICOLON,     // ;
  TT_ASSIGN,        // =

  // Logic operators
  TT_EQUAL,         // ==
  TT_NOT_EQUAL,     // !=
  TT_LOWER,         // <
  TT_LOWER_EQUAL,   // <=
  TT_GREATER,       // >
  TT_GREATER_EQUAL, // >=

  // Arithmetic operators
  TT_ADD,           // +
  TT_SUB,           // -
  TT_MUL,           // *
  TT_DIV,           // /
  TT_MOD,           // %
  TT_POW,           // ^

  // Keywords
  TT_PROGRAM,       // program
  TT_WHILE,         // while
  TT_DO,            // do
  TT_DONE,          // done
  TT_IF,            // if
  TT_THEN,          // then
  TT_ELSE,          // else
  TT_OUTPUT,        // output
  TT_TRUE,          // true
  TT_FALSE,         // false
  TT_READ,          // read
  TT_NOT,           // not

  // Others
  TT_NUMBER,        // number
  TT_VAR            // variable
};

extern const char *tt_str[];

const char* tt2str(enum TokenType type);

#endif /* TOKEN_TYPE_H */
