#ifndef ASM_H
#define ASM_H

#include "common.h"

static const char INIT_SECTION[] =
    "section .data\n"
    "\tfmtstr db \"Format string; text = %s\",10,0\n"
    "\ttext db \"Hello, world!\",0\n"
    "section .text\n"
    "\tglobal _start\n"
    "\textern printf\n"
    "\textern exit\n"
    "\tdefault rel\n"
    "_start:\n"
    "\tmov rdi,fmtstr\n"
    "\tmov rsi,text\n"
    "\tcall printf\n"
    "\tcall exit\n";

typedef struct {
  int count;
  int capacity;
  const char **sections;
} Asm;

void init_asm(Asm *);

#endif  // ASM_H
