#include "include/asm.h"

#include <stdio.h>
#include <stdlib.h>

#include "include/common.h"
#include "include/dyn_arr.h"
#include "include/value.h"

static const char DATA_SECTION[] =
    "section .data\n"
    "\tfmtdouble db \"%g\",10,0\n"
    "\tfmtstr db \"Format string; text = %s\",10,0\n"
    "\ttext db \"Hello, world!\",0\n";
static const char TEXT_SECTION[] =
    "section .text\n"
    "\tglobal _start\n"
    "\textern printf\n"
    "\textern exit\n"
    "\tdefault rel\n"
    "_start:\n"
    "\tmov rdi,fmtstr\n"
    "\tmov rsi,text\n"
    "\tcall printf\n";
static const char EXIT_SECTION[] = "\tcall exit\n";

static const char EXTERN_PRINTF[] = "\textern printf\n";
static const char CALL_PRINTF[] = "\tcall printf\n";
static const char MOV_RDI_DOUBLEFMT[] = "\tmov rdi,fmtdouble\n";
static const char MOV_RSI_COMMA[] = "\tmov rsi,";

INIT_DYN_ARR_FUN(init_asm, Asm, const char *, count, capacity, sections)
PUSH_DYN_ARR_FUN(push_section, Asm, const char *, count, capacity, sections)
POP_DYN_ARR_FUN(pop_section, Asm, const char *, count, capacity, sections)
DELETE_DYN_ARR_FUN(delete_asm, Asm, const char *, count, capacity, sections)

void push_data_section(Asm *asem) { push_section(asem, DATA_SECTION); }
void push_consts(Asm *asem) {
  for (int i = 0; i < asem->val_arr.count; ++i) {
    char *arg = (char *)malloc(50 * sizeof(char));
    sprintf(arg, "\tCONST_%d\tdq\t%g\n", i, *(asem->val_arr.values + i));
    push_section(asem, arg);
  }
}
void push_text_section(Asm *asem) { push_section(asem, TEXT_SECTION); }
void push_constant_printing(Asm *asem) {
  for (int i = 0; i < asem->val_arr.count; ++i) {
    char *arg = (char *)malloc(50 * sizeof(char));
    push_section(asem, MOV_RDI_DOUBLEFMT);
    push_section(asem, MOV_RSI_COMMA);
    sprintf(arg, "CONST_%d\n", i);
    push_section(asem, arg);
    push_section(asem, CALL_PRINTF);
  }
}
void push_exit_section(Asm *asem) { push_section(asem, EXIT_SECTION); }

int add_constant(Asm *asem, Value val) {
  push_value(&asem->val_arr, val);
  return asem->val_arr.count - 1;
}
