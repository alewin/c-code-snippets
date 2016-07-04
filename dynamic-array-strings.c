#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char **dirs = NULL;
  int count = 0;
  for (int i = 1; i < argc; i++) {
    int arraySize = (count + 1) * sizeof(char *);
    dirs = (char **)realloc(dirs, arraySize);
    if (dirs == NULL) {
      fprintf(stderr, "Realloc unsuccessful");
      exit(EXIT_FAILURE);
    }
    int stringSize = strlen(argv[i]) + 1;
    dirs[count] = (char *)malloc(stringSize);
    if (dirs[count] == NULL) {
      fprintf(stderr, "Malloc unsuccessful");
      exit(EXIT_FAILURE);
    }
    strcpy(dirs[count], argv[i]);
    count++;
  }
}
