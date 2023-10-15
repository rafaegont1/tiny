#include "command.h"
#include "../util/Memory.h"
#include <stdio.h>
#include <stdlib.h>

Command* cmd_init(void* data, const enum cmd type) {
  Command* cmd = (Command*) malloc(sizeof(Command));

  cmd->type = type;
  cmd->data = data;

  return cmd;
}

void cmd_execute(BlockCmd* cmds) {
  for (Command* iter = cmds->first; iter != NULL; iter = iter->next) {
    switch (iter->type) {
      case CMD_ASSIGN:
        mem_write((char*)((AssignCmd*)iter->data)->var->data,
                  expr_run(((AssignCmd*)iter->data)->expr));
        break;

      case CMD_BLOCKS:
        cmd_execute((BlockCmd*)iter->data);
        break;

      case CMD_IF:
        if (expr_run(((IfCmd*)iter->data)->cond)) {
          cmd_execute(((IfCmd*)iter->data)->thenCmds);
        } else if (((IfCmd*)iter->data)->elseCmds != NULL) {
          cmd_execute(((IfCmd*)iter->data)->elseCmds);
        }
        break;

      case CMD_OUTPUT:
        printf("%d\n", expr_run((Expr*)iter->data));
        break;

      case CMD_WHILE:
        while (expr_run(((WhileCmd*)iter->data)->cond)) {
          cmd_execute(((WhileCmd*)iter->data)->cmds);
        }
        break;
    }
  }
}
