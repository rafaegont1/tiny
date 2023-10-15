#include <stdio.h>
#include <stdlib.h>

#include "lexical/LexicalAnalysis.h"
#include "syntatic/SyntaticAnalysis.h"
#include "interpreter/command/command.h"
#include "interpreter/util/Memory.h"

int main(int argc, char* argv[])
{
  if (argc != 2) {
    printf("Usage: %s [Tiny program]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  LexicalAnalysis la;
  SyntaticAnalysis sa;
  BlockCmd* cmds;

  mem_init();
  la_init(&la, argv[1]);
  sa_init(&sa, &la);

  cmds = sa_start(&sa);
  cmd_execute(cmds);

  la_deinit(&la);
  blk_deinit(cmds);
  mem_deinit();

  return 0;
}
