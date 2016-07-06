#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// usage   char **files = NULL; int n =  dynamic_get_files(pathname, &files);
int dynamic_get_files(char *pathname, char ***files) {
  DIR *dir;
  int i = 0;
  struct dirent *ent;
  if ((dir = opendir(pathname)) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      if (ent->d_type == DT_REG) {
        *files = (char **)realloc(*files, (i + 1) * sizeof(char *));
        (*files)[i] = (char *)malloc((strlen(ent->d_name)) + 1);
        strcpy((*files)[i], ent->d_name);
        i++;
      }
    }
    closedir(dir);
  }
  return i;
}

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
