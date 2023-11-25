#ifndef ASM_H
#define ASM_H

#include "common.h"
#include "value.h"

typedef struct {
  int count;
  int capacity;
  const char **sections;
  ValueArray val_arr;
} Asm;

void init_asm(Asm *);
void push_asm(Asm *, const char *);
void pop_asm(Asm *);
void delete_asm(Asm *);

void push_data_section(Asm *);
void push_consts(Asm *);
void push_text_section(Asm *);
void push_constant_printing(Asm *);
void push_exit_section(Asm *);

int add_constant(Asm *, Value);

#endif  // ASM_H
