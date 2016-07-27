#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

int main( int argc, char** argv ) {
  if ( chdir("../bin") == -1 ) {
    printf( "chdir failed: %d\n", errno );
    return 1;
  }

  char buf[100];
  if ( getcwd( buf, sizeof(buf) ) != NULL ) {
    printf( "Working directory changed to: %s\n", buf );
  }

  if ( mkdir("newdir", 0644) == -1 ) {
    printf( "mkdir failed: %d\n", errno );
    return 1;
  }

  printf( "newdir created.\n" );

  if ( rmdir("newdir") == -1 ) {
    printf(" rmdir failed: %d\n", errno );
    return 1;
  }

  printf( "newdir removed.\n" );
}
