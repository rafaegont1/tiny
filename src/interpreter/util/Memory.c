#include "Memory.h"

map_int_t m_memory;

void mem_init() {
  map_init(&m_memory);
}

int mem_read(const char *name) {
  return *map_get(&m_memory, name);
}

void mem_write(const char *name, int value) {
  map_set(&m_memory, name, value);
}

void mem_deinit() {
  map_deinit(&m_memory);
}
