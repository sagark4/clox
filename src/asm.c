#include "include/asm.h"

#include <stdint.h>
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
static const char RAX_1_MOV_XMM0_QW[] = "\tmov rax,1\n\tmovsd xmm0, qword ";

INIT_DYN_ARR_FUN(init_asm, Asm, Section, count, capacity, sections)
PUSH_DYN_ARR_FUN(push_section, Asm, Section, count, capacity, sections)
POP_DYN_ARR_FUN(pop_section, Asm, Section, count, capacity, sections)
DELETE_DYN_ARR_FUN(delete_asm, Asm, Section, count, capacity, sections)

CREATE_DYN_ARR_FUNCS_STD_NAMES(HeapSections, char *, count, capacity, heap_sections)

void push_data_section(Asm *asem) {
  Section sec;
  sec.section = DATA_SECTION;
  sec.line = -1;
  push_section(asem, sec);
}

void push_consts(Asm *asem) {
  for (int i = 0; i < asem->constants.count; ++i) {
    char *arg = (char *)malloc(50 * sizeof(char));
    sprintf(arg, "\tCONST_%d\tdq\t%g\n", i, *(asem->constants.values + i));
    Section sec;
    sec.section = arg;
    sec.line = 1;
    push_section(asem, sec);
    push_HeapSections(&asem->heap_sections, arg);
  }
}
void push_text_section(Asm *asem) {
  Section sec;
  sec.section = TEXT_SECTION;
  sec.line = INT32_MAX;
  push_section(asem, sec);
}
void push_constant_printing(Asm *asem) {
  for (int i = 0; i < asem->constants.count; ++i) {
    char *arg = (char *)malloc(50 * sizeof(char));
    Section sec;
    sec.section = MOV_RDI_DOUBLEFMT;
    sec.line = i;

    push_section(asem, sec);
    sec.section = RAX_1_MOV_XMM0_QW;
    push_section(asem, sec);

    sprintf(arg, "[CONST_%d]\n", i);
    sec.section = arg;
    push_section(asem, sec);
    push_HeapSections(&asem->heap_sections, arg);
    sec.section = CALL_PRINTF;
    push_section(asem, sec);
  }
}
void push_exit_section(Asm *asem) {
  Section sec;
  sec.section = EXIT_SECTION;
  sec.line = INT32_MAX;
  push_section(asem, sec);
}

int add_constant(Asm *asem, Value val) {
  push_value(&asem->constants, val);
  return asem->constants.count - 1;
}

void free_heap_sections(HeapSections *heap_sections) {
  for (int i = 0; i < heap_sections->count; ++i) {
    free(*(heap_sections->heap_sections + i));
  }
}
