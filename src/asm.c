#include "include/asm.h"

#include <stdlib.h>

#include "include/dyn_arr.h"

#define SECTIONS_INIT_CAPACITY 8

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

INIT_DYN_ARR_FUN(init_asm, Asm, const char *, count, capacity, sections)
PUSH_DYN_ARR_FUN(push_section, Asm, const char *, count, capacity, sections)
POP_DYN_ARR_FUN(pop_section, Asm, const char *, count, capacity, sections)
DELETE_DYN_ARR_FUN(delete_asm, Asm, const char *, count, capacity, sections)

void push_init_section(Asm *asem) { push_section(asem, INIT_SECTION); }
