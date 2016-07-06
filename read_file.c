#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Expected 1 parameter");
    return (EXIT_FAILURE);
  }
  FILE *stream;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int i = 1;
  const char *pathname = argv[1];

  stream = fopen(pathname, "r");
  if (stream == NULL)
    exit(EXIT_FAILURE);

  while (((read = getline(&line, &len, stream)) != -1)) {
    printf("Retrieved line %d of length %zu :\n", i, read);
    printf("%s", line);
    i++;
  }

  free(line);
  fclose(stream);
  exit(EXIT_SUCCESS);
}
