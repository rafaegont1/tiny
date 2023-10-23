#include "expr.h"
#include "../util/Memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int expr_binaryInt(BinaryInt* intergers);
int expr_singleBoll(SingleBool* boolean);

Expr* expr_init(void* data, const enum expr type) {
  Expr* expr = (Expr*) malloc(sizeof(Expr));

  expr->type = type;
  expr->data = data;

  return expr;
}

void expr_deinit(Expr* expr) {
  if (expr->type == EXPR_BINARY_INT) {
    expr_deinit(((BinaryInt*)expr->data)->left);
    expr_deinit(((BinaryInt*)expr->data)->right);
  } else if (expr->type == EXPR_SINGLE_BOOL) {
    expr_deinit(((SingleBool*)expr->data)->left);
    expr_deinit(((SingleBool*)expr->data)->right);
  }

  free((BinaryInt*)expr->data);
  free(expr);
}

int expr_run(Expr* expr) {
  int value;

  switch (expr->type) {
    case EXPR_CONST_INT:
    case EXPR_CONST_BOOL:
      value = *((int*)expr->data);
      break;

    case EXPR_NEG_INT:
      value = -expr_run((Expr*)expr->data);
      break;

    case EXPR_READ_INT:
      scanf("%d", &value);
      break;

    case EXPR_BINARY_INT:
      value = expr_binaryInt((BinaryInt*)expr->data);
      break;

    case EXPR_VARIABLE:
      value = mem_read((char*)expr->data);
      break;

    case EXPR_SINGLE_BOOL:
      value = expr_singleBoll((SingleBool*)expr->data);
      break;

    case EXPR_NOT_BOOL:
      value = !expr_run((Expr*)expr->data);
      break;
  }

  return value;
}

/* _____ Auxiliary functions _____ */

int expr_binaryInt(BinaryInt* intergers) {
  int v1 = expr_run(intergers->left);
  int v2 = expr_run(intergers->right);
  int value;

  switch (intergers->op) {
    case OP_ADD:
      value = v1 + v2;
      break;

    case OP_SUB:
      value = v1 - v2;
      break;

    case OP_MUL:
      value = v1 * v2;
      break;

    case OP_DIV:
      value = v1 / v2;
      break;

    case OP_MOD:
      value = v1 % v2;
      break;

    case OP_POW:
      //value = (int) pow(v1, v2);
      if (v2 == 0) return 1;
      value = v1;
      for (int i = 1; i < v2; i++) {
        value *= v1;
      }
      break;
  }

  return value;
}

int expr_singleBoll(SingleBool* booleans) {
  int v1 = expr_run(booleans->left);
  int v2 = expr_run(booleans->right);
  int value;

  switch (booleans->op) {
  case OP_EQUAL:
    value = v1 == v2;
    break;

  case OP_NOT_EQUAL:
    value = v1 != v2;
    break;

  case OP_LOWER:
    value = v1 < v2;
    break;

  case OP_GREATER:
    value = v1 > v2;
    break;

  case OP_LOWER_EQUAL:
    value = v1 <= v2;
    break;

  case OP_GREATER_EQUAL:
    value = v1 >= v2;
    break;
  }

  return value;
}
