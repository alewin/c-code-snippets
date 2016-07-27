#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main( int argc, char** argv ) {
  char buf[100];
  if ( getcwd( buf, sizeof(buf) ) != NULL ) {
    printf( "/bin/ls %s\n", buf );
  }
  else {
    printf( "getcwd failed with err: %d\n", errno );
  }

  if ( fork() == 0 ) {
    char* args[] = { "/bin/ls", NULL };
    if ( execve( args[0], args, NULL ) == -1 ) {
      switch (errno) {
      default:
        printf( "execve failed with err: %d\n", errno );
        break;
      }
    }
  }
  else {
  }
}
