#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "TokenType.h"
#include "../map/map.h"
#include <stdbool.h>

void st_init(map_int_t *symbol_table);
bool st_contains(map_int_t *symbol_table, const char *token);
enum TokenType st_find(map_int_t *symbol_table, const char *token);

#endif /* SYMBOL_TABLE_H */
