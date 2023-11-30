#include <stdio.h>
#include <stdlib.h>

#include "include/compiler.h"

static char *read_file(const char *);

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: cloxc filename.\n");
    exit(64);
  }
  char *source = read_file(argv[1]);
  compile(source);
  return 0;
}

static char *read_file(const char *path) {
  FILE *fp;
  if (!(fp = fopen(path, "rb"))) {
    fprintf(stderr, "Error fopen-ing file %s.  Exiting.\n", path);
    exit(74);
  }
  if (fseek(fp, 0, SEEK_END)) {
    fprintf(stderr, "Error fseek-ing file %s.  Exiting.\n", path);
    exit(-1);
  }
  int size = ftell(fp);
  rewind(fp);
  char *text = (char *)malloc(size + 1);
  if (text == NULL) {
    fprintf(stderr, "Could not get enough memory.\n");
  }
  int bytes_read = fread(text, sizeof(char), size, fp);
  if (bytes_read != size) {
    fprintf(stderr, "Could not read the whole file %s.\n", path);
  }
  fclose(fp);
  *(text + size) = '\0';
  return text;
}
