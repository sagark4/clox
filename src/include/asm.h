#ifndef ASM_H
#define ASM_H

#include "common.h"
#include "value.h"

typedef struct {
  int count;
  int capacity;
  char **heap_sections;
} HeapSections;

void init_dynarr_HeapSections(HeapSections *);
void push_HeapSections(HeapSections *, char *);
char *pop_HeapSections(HeapSections *);
void delete_dynarr_HeapSections(HeapSections *);

typedef struct {
  const char *section;
  int line;
} Section;

typedef struct {
  int count;
  int capacity;
  Section *sections;
  ValueArray constants;
  HeapSections heap_sections;
} Asm;

void init_asm(Asm *);
void push_asm(Asm *, Section);
Section *pop_asm(Asm *);
void delete_asm(Asm *);

void push_data_section(Asm *);
void push_consts(Asm *);
void push_text_section(Asm *);
void push_constant_printing(Asm *);
void push_exit_section(Asm *);

int add_constant(Asm *, Value);
void free_heap_sections(HeapSections *);
#endif  // ASM_H
