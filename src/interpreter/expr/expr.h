#ifndef EXPR_H
#define EXPR_H

enum expr {
  // IntExpr
  EXPR_CONST_INT,
  EXPR_NEG_INT,
  EXPR_READ_INT,
  EXPR_BINARY_INT,
  EXPR_VARIABLE,

  // BoolExpr
  EXPR_CONST_BOOL,
  EXPR_SINGLE_BOOL,
  EXPR_NOT_BOOL
};

enum int_op { OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD };

enum bool_op {
  OP_EQUAL, OP_NOT_EQUAL,
  OP_LOWER, OP_GREATER,
  OP_LOWER_EQUAL, OP_GREATER_EQUAL
};

typedef struct Expr Expr;
typedef struct BinaryInt BinaryInt;
typedef struct SingleBool SingleBool;

struct Expr {
  enum expr type;
  void* data;
};

struct BinaryInt {
  Expr* left;
  enum int_op op;
  Expr* right;
};

struct SingleBool {
  Expr* left;
  enum bool_op op;
  Expr* right;
};

Expr* expr_init(void* data, const enum expr type);
void expr_deinit(Expr* expr);
int expr_run(Expr* expr);

#endif /* EXPR_H */
