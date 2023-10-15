#ifndef LIST_H
#define LIST_H

#include "../expr/expr.h"

enum cmd {
  CMD_ASSIGN, CMD_BLOCKS, CMD_IF,
  CMD_OUTPUT, CMD_WHILE
};

typedef struct BlockCmd BlockCmd;
typedef struct Command Command;
typedef struct IfCmd IfCmd;
typedef struct AssignCmd AssignCmd;
typedef struct WhileCmd WhileCmd;

struct Command {
  enum cmd type;
  void* data;
  struct Command* next;
};

struct BlockCmd {
  struct Command* first;
  struct Command* last;
};

struct AssignCmd {
  Expr* expr;
  Expr* var;
};

struct IfCmd {
  Expr* cond;
  BlockCmd* thenCmds;
  BlockCmd* elseCmds;
};

struct WhileCmd {
  Expr* cond;
  BlockCmd* cmds;
};

void blk_init(BlockCmd* cmds);
void blk_deinit(BlockCmd* cmds);
void blk_set(BlockCmd* cmds, Command* new_node);

#endif /* LIST_H */
