#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

void* tmain(void* arg) {
  printf( "[thread %08lx] thread group id (pid): %d\n",
         (unsigned long)pthread_self(), getpid() ); // requires <unistd.h>
  return NULL;
}

int main ( int argc, char** argv ) {

  pthread_t tid;

  if ( pthread_create(&tid, NULL, &tmain, NULL) == 0 ) {
    printf("[main] pthread created: %08lx\n", (unsigned long)tid);
  }
  else {
    printf("[main] pthread creation has failed: %s\n", strerror(errno));
  }

  printf("[main] thread group id (pid): %d\n", getpid());

  exit(0); // requires <stdlib.h>
}
