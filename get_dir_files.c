#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Expected 1 parameter");
    return -1;
  }
  char *pathanme = argv[1];
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir(pathanme)) != NULL) {
    // print all the files
    while ((ent = readdir(dir)) != NULL) {
      if (ent->d_type == DT_REG)
        printf("%s\n", ent->d_name);
    }
    closedir(dir);
  } else {
    // could not open directory
    perror("");
    return -1;
  }
}
