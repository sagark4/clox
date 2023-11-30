#include "include/compiler.h"

#include "include/asm.h"
#include "include/value.h"

void generate_asem(Asm *);

void compile(const char *source) {
  Asm asem;
  init_asm(&asem);
  init_val_arr(&asem.constants);
  init_dynarr_HeapSections(&asem.heap_sections);
  add_constant(&asem, 3.14159);
  add_constant(&asem, 2 * 3.14159);
  push_data_section(&asem);
  push_consts(&asem);
  push_text_section(&asem);
  push_constant_printing(&asem);
  push_exit_section(&asem);
  generate_asem(&asem);
  free_heap_sections(&asem.heap_sections);
  delete_dynarr_HeapSections(&asem.heap_sections);
  delete_val_arr(&asem.constants);
  delete_asm(&asem);
}

void generate_asem(Asm *asem) {
  FILE *fp = fopen("asem.asm", "wb");
  printf("%p\n", fp);
  if (fp != NULL) {
    for (int i = 0; i < asem->count; ++i) {
      fputs(asem->sections[i].section, fp);
    }
    fclose(fp);
  }
}
