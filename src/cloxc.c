#include <stdio.h>

#include "include/asm.h"
#include "include/common.h"
#include "include/value.h"

void generate_asem(Asm *);

int main(int argc, const char *argv[]) {
  Asm asem;
  init_asm(&asem);
  init_val_arr(&asem.val_arr);
  printf("Initialized asem and val_arr.\n");
  add_constant(&asem, 3.14159);
  add_constant(&asem, 2 * 3.14159);
  push_data_section(&asem);
  push_consts(&asem);
  push_text_section(&asem);
  push_constant_printing(&asem);
  push_exit_section(&asem);
  generate_asem(&asem);
  delete_val_arr(&asem.val_arr);
  delete_asm(&asem);
  return 0;
}

void generate_asem(Asm *asem) {
  FILE *fp = fopen("asem.asm", "ab");
  if (fp != NULL) {
    for (int i = 0; i < asem->count; ++i) {
      fputs(asem->sections[i], fp);
    }
    fclose(fp);
  }
}
