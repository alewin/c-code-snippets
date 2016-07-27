#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char** argv) {
  char* filepath = "../bin/stat.dat";

  int fd = open( filepath, O_CREAT | O_TRUNC, 0600 );
  if ( fd == -1 ) {
    printf( "Failed to open file due to err: %d\n", errno );
    return 1;
  }

  struct stat st;
  if ( fstat(fd, &st) != -1 ) {
    printf( "[%s]\n", filepath );
    printf( "  uid: %d\n", st.st_uid );
    printf( "  gid: %d\n", st.st_gid );
    printf( "  type: ");
    if (S_ISREG(st.st_mode)) {
      printf( "regular file\n" );
    }
    else if (S_ISDIR(st.st_mode)) {
      printf( "directory\n" );
    }
  }
  else {
    printf( "Failed to call fstat due to err: %d\n", errno );
    close(fd);
    return 1;
  }

  close(fd);
}
