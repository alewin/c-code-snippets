#include <sys/mman.h>   /* mmap */
#include <sys/fcntl.h>  /* open */
#include <unistd.h>     /* write, close */
#include <string.h>     /* strlen */
#include <stdio.h>
#include <errno.h>

int main ( int argc, char** argv ) {
  char* filepath = "../bin/mm.dat";

  int fd = open( filepath, O_CREAT | O_TRUNC | O_RDWR, 0600 );
  if ( fd == -1 ) {
    printf( "[mm] ERROR file creation failed: %d\n", errno );
    return 1;
  }

  printf( "[mm] file created: %s\n", filepath );

  char* msg = "Hello, world!";
  if ( write( fd, msg, strlen(msg) ) == -1 ) {
    switch ( errno ) {
    case EBADF:
      printf( "[mm] WARNING file write error: Bad file descriptor\n" );
      break;
    default:
      printf( "[mm] WARNING file write error: %d\n", errno );
      break;
    }
  }

  /*
   * void *mmap(void *addr, size_t length, int prot, int flags,
   *            int fd, off_t offset);
   *  int  munmap(void *addr, size_t length);
   */
  int length = strlen( msg );
  char* addr = mmap( NULL,
                     length,
                     PROT_READ,
                     MAP_PRIVATE,
                     fd,
                     0 );

  if (addr == MAP_FAILED) {
    printf( "[mm] ERROR map failed: %d\n", errno );
  }
  else {
    printf( "[mm] mapped file addr: %p\n", (void *)addr );
    printf( "[mm] mapped file read: %.*s\n", length, addr );

    if ( munmap( addr, length ) == -1 ) {
      printf( "[mm] file unmap failed: %d\n", errno );
    }
    else {
      printf( "[mm] file unmmapped.\n" );
    }
  }

  close( fd );
}
