#ifndef ASM_H
#define ASM_H

#include "common.h"

typedef struct {
  int count;
  int capacity;
  const char **sections;
} Asm;

void init_asm(Asm *);
void push_asm(Asm *, const char *);
void pop_asm(Asm *);
void delete_asm(Asm *);
    
void push_init_section(Asm *);
#endif  // ASM_H
