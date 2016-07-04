#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// usage   char **files = NULL; int n = 0; get_c_files(pathname, &files, n);
void dynamic_get_files(char *pathname, char ***cfiles, int i) {
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir(pathname)) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      if (ent->d_type == DT_REG) {
        *cfiles = realloc(*cfiles, (i + 1) * sizeof(char *));
        (*cfiles)[i] = malloc((strlen(ent->d_name)) + 1);
        strcpy((*cfiles)[i], ent->d_name);
        i++;
      }
    }
    printf("files[%d] = %s \n", 0, (*cfiles)[0]);
    closedir(dir);
  }
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
