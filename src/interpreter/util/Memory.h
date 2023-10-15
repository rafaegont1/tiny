#ifndef MEMORY_H
#define MEMORY_H

#include "../../map/map.h"

void mem_init();
int mem_read(const char *name);
void mem_write(const char *name, int value);
void mem_deinit();

#endif /* MEMORY_H */
