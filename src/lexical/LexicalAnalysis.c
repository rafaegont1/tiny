#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LexicalAnalysis.h"

void la_init(LexicalAnalysis *la, const char* filename)
{
  la->input = fopen(filename, "r");
  if (!la->input) {
    printf("Unable to open \"%s\" file\n", filename);
    exit(EXIT_FAILURE);
  }

  st_init(&la->symbol_table);
  la->line = 1;
}

void la_deinit(LexicalAnalysis *la)
{
  fclose(la->input);
  map_deinit(&la->symbol_table);
}

Lexeme la_nextToken(LexicalAnalysis *la)
{
  int state = 1;
  Lexeme lex;
  size_t token_sz = 0;

  lx_init(&lex);

  while (state != 7 && state != 8) {
    int c = fgetc(la->input);

    //printf("[%d, %d ('%c')]", state, c, c);

    switch (state) {
      case 1:
        if (c == ' ' || c == '\t' || c == '\r') {
          state = 1;
        } else if (c == '\n') {
          ++la->line;
          state = 1;
        } else if (c == '#') {
          state = 2;
        } else if (c == '=' || c == '<' || c == '>') {
          lex.token[token_sz++] = c;
          state = 3;
        } else if (c == '!') {
          lex.token[token_sz++] = c;
          state = 4;
        } else if (c == ';' || c == '+' || c == '-' ||
            c == '*' || c == '/' || c == '%') {
          lex.token[token_sz++] = c;
          state = 7;
        } else if (c == '_' || isalpha(c)) {
          lex.token[token_sz++] = c;
          state = 5;
        } else if (isdigit(c)) {
          lex.token[token_sz++] = c;
          state = 6;
        } else {
          if (c == -1) {
            lex.type = TT_END_OF_FILE;
            state = 8;
          } else {
            lex.token[token_sz++] = c;
            lex.type = TT_INVALID_TOKEN;
            state = 8;
          }
        }
        break;

      case 2:
        if (c == '\n') {
          ++la->line;
          state = 1;
        } else if (c == -1) {
          lex.type = TT_END_OF_FILE;
          state = 8;
        } else {
          state = 2;
        }
        break;

      case 3:
        if (c == '=') {
          lex.token[token_sz++] = c;
          state = 7;
        } else {
          if (c != -1) ungetc(c, la->input);
          state = 7;
        }
        break;

      case 4:
        if (c == '=') {
          lex.token[token_sz++] = c;
          state = 7;
        } else {
          if (c == -1) {
            lex.type = TT_UNEXPECTED_EOF;
            state = 8;
          } else {
            lex.type = TT_INVALID_TOKEN;
            state = 8;
          }
        }
        break;

      case 5:
        if (c == '_' || isalpha(c) || isdigit(c)) {
          lex.token[token_sz++] = c;
          state = 5;
        } else {
          if (c != -1) ungetc(c, la->input);
          state = 7;
        }
        break;

      case 6:
        if (isdigit(c)) {
          lex.token[token_sz++] = c;
          state = 6;
        } else {
          if (c != -1) ungetc(c, la->input);
          lex.type = TT_NUMBER;
          state = 8;
        }
        break;

      default:
        printf("invalid state\n");
        break;
    }
  }

  lex.token[token_sz] = '\0';

  if (state == 7) lex.type = st_find(&la->symbol_table, lex.token);

  return lex;
}
