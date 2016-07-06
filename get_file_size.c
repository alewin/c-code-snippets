#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

off_t fsize(const char *filename) {
  struct stat st;
  if (stat(filename, &st) == 0)
    return st.st_size;
  fprintf(stderr, "Cannot determine size of %s: %s\n", filename,
          strerror(errno));
  return -1;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Expected 1 parameter");
    return -1;
  }
  char *file = argv[1];
  off_t s = fsize(file);
  return 0;
}
