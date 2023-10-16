#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "SyntaticAnalysis.h"
#include "../interpreter/expr/expr.h"

void sa_eat(SyntaticAnalysis* sa, const enum TokenType type);
void sa_showError(SyntaticAnalysis* sa);
BlockCmd* sa_program(SyntaticAnalysis* sa);
BlockCmd* sa_cmdList(SyntaticAnalysis* sa);
Command* sa_cmd(SyntaticAnalysis* sa);
Command* sa_assign(SyntaticAnalysis* sa);
Command* sa_output(SyntaticAnalysis* sa);
Command* sa_if(SyntaticAnalysis* sa);
Command* sa_while(SyntaticAnalysis* sa);
Expr* sa_boolExpr(SyntaticAnalysis* sa);
Expr* sa_intExpr(SyntaticAnalysis* sa);
Expr* sa_intTerm(SyntaticAnalysis* sa);
Expr* sa_var(SyntaticAnalysis* sa);
Expr* sa_const(SyntaticAnalysis* sa);

void sa_init(SyntaticAnalysis* sa, LexicalAnalysis* la) {
  sa->la = la;
  sa->lex = la_nextToken(la);
}

BlockCmd* sa_start(SyntaticAnalysis* sa) {
  BlockCmd* cmd = sa_program(sa);
  sa_eat(sa, TT_END_OF_FILE);
  return cmd;
}

void sa_eat(SyntaticAnalysis* sa, const enum TokenType type) {
  //printf("Expected (..., %s), found (\"%s\" %s)\n", tt2str(type),
  //                                                  sa->lex.token,
  //                                                  tt2str(sa->lex.type));
  if (type == sa->lex.type) sa->lex = la_nextToken(sa->la);
  else sa_showError(sa);
}

void sa_showError(SyntaticAnalysis* sa) {
  printf("Line %02d: ",sa->la->line);

  switch (sa->lex.type) {
    case TT_INVALID_TOKEN:
      printf("invalid lexeme [%s]\n", sa->lex.token);
      break;

    case TT_UNEXPECTED_EOF:
    case TT_END_OF_FILE:
      printf("unexpected end of file\n");
      break;

    default:
      printf("unexpected lexeme [%s]\n", sa->lex.token);
      break;
  }

  exit(EXIT_FAILURE);
}

// <program>   ::= program <cmdlist>
BlockCmd* sa_program(SyntaticAnalysis* sa) {
  sa_eat(sa, TT_PROGRAM);
  return sa_cmdList(sa);
}

// <cmdlist>   ::= <cmd> { <cmd> }
BlockCmd* sa_cmdList(SyntaticAnalysis* sa) {
  BlockCmd* cmds = (BlockCmd*) malloc(sizeof(BlockCmd));
  Command* cmd;

  blk_init(cmds);
  cmd = sa_cmd(sa);
  blk_set(cmds, cmd);

  while (sa->lex.type == TT_VAR ||
         sa->lex.type == TT_OUTPUT ||
         sa->lex.type == TT_IF ||
         sa->lex.type == TT_WHILE) {
    cmd = sa_cmd(sa);
    blk_set(cmds, cmd);
  }

  return cmds;
}

// <cmd>       ::= (<assign> | <output> | <if> | <while>) ;
Command* sa_cmd(SyntaticAnalysis* sa) {
  Command* cmd;

  switch (sa->lex.type) {
    case TT_VAR:
      cmd = sa_assign(sa);
      break;

    case TT_OUTPUT:
      cmd = sa_output(sa);
      break;

    case TT_IF:
      cmd = sa_if(sa);
      break;

    case TT_WHILE:
      cmd = sa_while(sa);
      break;

    default:
      sa_showError(sa);
      break;
  }

  sa_eat(sa, TT_SEMICOLON);

  return cmd;
}

// <assign>    ::= <var> = <intexpr>
Command* sa_assign(SyntaticAnalysis* sa) {
  AssignCmd* assign = (AssignCmd*) malloc(sizeof(AssignCmd));

  assign->var = sa_var(sa);
  sa_eat(sa, TT_ASSIGN);
  assign->expr = sa_intExpr(sa);

  return cmd_init((void*)assign, CMD_ASSIGN);
}

// <output>    ::= output <intexpr>
Command* sa_output(SyntaticAnalysis* sa) {
  Expr* interger;

  sa_eat(sa, TT_OUTPUT);
  interger = sa_intExpr(sa);

  return cmd_init((void*)interger, CMD_OUTPUT);
}

// <if>        ::= if <boolexpr> then <cmdlist> [ else <cmdlist> ] done
Command* sa_if(SyntaticAnalysis* sa) {
  IfCmd* conditional = (IfCmd*) malloc(sizeof(IfCmd));
  sa_eat(sa, TT_IF);

  conditional->cond = sa_boolExpr(sa);
  sa_eat(sa, TT_THEN);
  conditional->thenCmds = sa_cmdList(sa);

  if (sa->lex.type == TT_ELSE) {
    sa->lex = la_nextToken(sa->la);
    conditional->elseCmds = sa_cmdList(sa);
  } else {
    conditional->elseCmds = NULL;
  }

  sa_eat(sa, TT_DONE);

  return cmd_init((void*)conditional, CMD_IF);
}

// <while>     ::= while <boolexpr> do <cmdlist> done
Command* sa_while(SyntaticAnalysis* sa) {
  WhileCmd* loop = (WhileCmd*) malloc(sizeof(WhileCmd));

  sa_eat(sa, TT_WHILE);
  loop->cond = sa_boolExpr(sa);
  sa_eat(sa, TT_DO);
  loop->cmds = sa_cmdList(sa);
  sa_eat(sa, TT_DONE);

  return cmd_init((void*)loop, CMD_WHILE);
}

// <boolexpr>  ::= false | true |
//                 not <boolexpr> |
//                 <intterm> (== | != | < | > | <= | >=) <intterm>
Expr* sa_boolExpr(SyntaticAnalysis* sa) {
  SingleBool* bool_expr;
  int* value;

  if (sa->lex.type == TT_FALSE) {

    sa->lex = la_nextToken(sa->la);
    value = (int*) malloc(sizeof(int));
    *value = 0;
    return expr_init((void*)value, EXPR_CONST_BOOL);

  } else if (sa->lex.type == TT_TRUE) {

    sa->lex = la_nextToken(sa->la);
    value = (int*) malloc(sizeof(int));
    *value = 1;
    return expr_init((void*)value, EXPR_CONST_BOOL);

  } else if (sa->lex.type == TT_NOT) {

    sa->lex = la_nextToken(sa->la);
    Expr* tmp = sa_boolExpr(sa);
    return expr_init((void*)tmp, EXPR_NOT_BOOL);

  } else {
    bool_expr = (SingleBool*) malloc(sizeof(SingleBool));
    bool_expr->left = sa_intTerm(sa);

    switch (sa->lex.type) {
      case TT_EQUAL:
        bool_expr->op = OP_EQUAL;
        break;

      case TT_NOT_EQUAL:
        bool_expr->op = OP_NOT_EQUAL;
        break;

      case TT_LOWER:
        bool_expr->op = OP_LOWER;
        break;

      case TT_GREATER:
        bool_expr->op = OP_GREATER;
        break;

      case TT_LOWER_EQUAL:
        bool_expr->op = OP_LOWER_EQUAL;
        break;

      case TT_GREATER_EQUAL:
        bool_expr->op = OP_GREATER_EQUAL;
        break;

      default:
        sa_showError(sa);
    }

    sa->lex = la_nextToken(sa->la);
    bool_expr->right = sa_intTerm(sa);

    return expr_init((void*)bool_expr, EXPR_SINGLE_BOOL);
  }
}

// <intexpr>   ::= [ + | - ] <intterm> [ (+ | - | * | / | %) <intterm> ]
Expr* sa_intExpr(SyntaticAnalysis* sa) {
  Expr* int_expr;
  bool is_negative = false;

  if (sa->lex.type == TT_ADD) {
    sa->lex = la_nextToken(sa->la);
  } else if (sa->lex.type == TT_SUB) {
    sa->lex = la_nextToken(sa->la);
    is_negative = true;
  }

  int_expr = sa_intTerm(sa);

  if (is_negative) {
    int_expr = expr_init((void*)int_expr, EXPR_NEG_INT);
  }

  if (sa->lex.type == TT_ADD ||
      sa->lex.type == TT_SUB ||
      sa->lex.type == TT_MUL ||
      sa->lex.type == TT_DIV ||
      sa->lex.type == TT_MOD) {
    BinaryInt* bin = (BinaryInt*) malloc(sizeof(BinaryInt));

    switch (sa->lex.type) {
      case TT_ADD:
        bin->op = OP_ADD;
        break;

      case TT_SUB:
        bin->op = OP_SUB;
        break;

      case TT_MUL:
        bin->op = OP_MUL;
        break;

      case TT_DIV:
        bin->op = OP_DIV;
        break;

      case TT_MOD:
        bin->op = OP_MOD;
        break;

      default:
        sa_showError(sa);
    }

    sa->lex = la_nextToken(sa->la);
    bin->left = int_expr;
    bin->right = sa_intTerm(sa);
    int_expr = expr_init((void*)bin, EXPR_BINARY_INT);
  }

  return int_expr;
}

// <intterm>   ::= <var> | <const> | read
Expr* sa_intTerm(SyntaticAnalysis* sa) {
  Expr* interger;

  switch(sa->lex.type) {
    case TT_VAR:
      interger = sa_var(sa);
      break;

    case TT_NUMBER:
      interger = sa_const(sa);
      break;

    case TT_READ:
      interger = expr_init(NULL, EXPR_READ_INT);
      sa->lex = la_nextToken(sa->la);
      break;

    default:
      sa_showError(sa);
  }

  return interger;
}

// <var>       ::= id
Expr* sa_var(SyntaticAnalysis* sa) {
  char* var_name = (char*) malloc(strlen(sa->lex.token) + 1);

  strcpy(var_name, sa->lex.token);
  sa->lex = la_nextToken(sa->la);

  return expr_init((void*)var_name, EXPR_VARIABLE);
}

// <const>     ::= number
Expr* sa_const(SyntaticAnalysis* sa) {
  int* value = (int*) malloc(sizeof(int));

  *value = atoi(sa->lex.token);
  sa->lex = la_nextToken(sa->la);

  return expr_init((void*)value, EXPR_CONST_INT);
}
