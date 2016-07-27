#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

int main( int argc, char** argv ) {

  printf( "size of time_t: %lu\n", sizeof(time_t) );

  int sec = 2;
  while ( sec-- > 0 ) {
    time_t t = time( NULL );
    struct timeval tv;
    if( gettimeofday(&tv, NULL) == 0 ) {
      printf( "time: %lu (sec), %d (usec)\n", tv.tv_sec, tv.tv_usec );
    }
    printf( "time: %lu\n (sec)", t );
    sleep(1);
  }
}
