#include "include/asm.h"

#include <stdlib.h>

void init_asm(Asm *asem) {
  asem->count = 1;
  asem->capacity = 1;
  asem->sections = malloc(sizeof(char *));
  asem->sections[0] = INIT_SECTION;
}
