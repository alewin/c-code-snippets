#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main( int argc, char** argv ) {

  int pd[2];

  if ( pipe(pd) == -1 ) {
    printf( "pipe creation failed: %d\n", errno );
    return 1;
  }

  if ( fork() == 0 ) {
    close( pd[1] );          /* Close unused write end */

    char buf;

    printf( "[child] " );

    while ( read( pd[0], &buf, sizeof(buf) ) > 0 ) {
      printf( "%c", buf );
    }

    printf( "\n" );

    close( pd[0] );
  }
  else {
    close( pd[0] );          /* Close unused read end */

    char* msg = "Hello, world!";
    printf( "[parent] %s (len=%lu)\n", msg, strlen(msg) );
    write( pd[1], msg, strlen(msg) );
    close( pd[1] );          /* Reader will see EOF */

    int child_status;
    wait( &child_status );
  }
}
