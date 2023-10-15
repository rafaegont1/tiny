#include "block.h"
#include "../expr/expr.h"
#include <stdlib.h>

void blk_init(BlockCmd* cmds) {
  cmds->first = cmds->last = NULL;
}

void blk_deinit(BlockCmd* cmds) {
  Command* iter = cmds->first;

  while (iter != NULL) {
    Command* rm = iter;

    iter = iter->next;

    switch (rm->type) {
      case CMD_BLOCKS:
        blk_deinit((BlockCmd*)iter->data);
        break;

      case CMD_ASSIGN:
        expr_deinit(((AssignCmd*)rm->data)->expr);
        expr_deinit(((AssignCmd*)rm->data)->var);
        break;

      case CMD_IF:
        expr_deinit(((IfCmd*)rm->data)->cond);
        blk_deinit(((IfCmd*)rm->data)->thenCmds);
        blk_deinit(((IfCmd*)rm->data)->elseCmds);
        break;

      case CMD_WHILE:
        expr_deinit(((WhileCmd*)rm->data)->cond);
        blk_deinit(((WhileCmd*)rm->data)->cmds);
        break;

      default:
        expr_deinit((Expr*)rm->data);
        break;
    }

    free(rm);
  }

  cmds->first = cmds->last = NULL;
}

void blk_set(BlockCmd* cmds, Command* new_node) {
  new_node->next = NULL;

  if (cmds->first == NULL) {
    cmds->first = cmds->last = new_node;
  } else {
    cmds->last = cmds->last->next = new_node;
  }
}
