#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *remove_ext(const char *mystr) {
  char *retstr;
  char *lastdot;
  if (mystr == NULL)
    return NULL;
  if ((retstr = (char *)malloc(strlen(mystr) + 1)) == NULL)
    return NULL;
  strcpy(retstr, mystr);
  lastdot = strrchr(retstr, '.');
  if (lastdot != NULL)
    *lastdot = '\0';
  return retstr;
}
int main(int argc, char *argv[]) {
  printf("%s\n", remove_ext("ciao.c.o"));
  return 1;
}
