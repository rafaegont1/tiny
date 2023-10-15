#ifndef COMMAND_H
#define COMMAND_H

#include "block.h"
#include "../expr/expr.h"

Command* cmd_init(void* data, const enum cmd type);
void cmd_execute(BlockCmd* cmds);

#endif /* COMMAND_H */
