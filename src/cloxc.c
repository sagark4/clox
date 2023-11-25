#include "include/asm.h"
#include "include/common.h"

void generate_asem(Asm *);

int main(int argc, const char *argv[]) {
  Asm asem;
  init_asm(&asem);
  generate_asem(&asem);
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
