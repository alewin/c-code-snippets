#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>

int main( int argc, char** argv ) {

  int nsems = 1;
  int semid = semget( IPC_PRIVATE, nsems, IPC_CREAT | 0600 );

  if (semid == -1) {
    switch (errno) {
    case EEXIST:
      printf( "semaphore already exists.\n" );
      break;
    default:
      printf( "semget failed with err: %d\n", errno );
      break;
    }
    return -1;
  }

  struct sembuf ops[3];

  ops[0].sem_num = 0;
  ops[0].sem_op = 1; // Add 1 to semval.
  ops[0].sem_flg = 0;

  if ( semop( semid, ops, 1 ) == 0 ) {
    printf( "[main] semophore initialized to 1.\n" );
  }
  else {
    printf( "[main] semop 0 got an error: %d\n", errno );
  }

  if ( fork() == 0 ) {
    ops[1].sem_num = 0;
    ops[1].sem_op = 0; // Wait until semval becomes 0.
    ops[1].sem_flg = 0;

    printf( "[child] semaphore wait started.\n" );

    if ( semop( semid, ops + 1, 1 ) == 0 ) {
      printf( "[child] semaphore wait finished.\n" );
    }
    else {
      printf( "[child] semop 1 got an error: %d\n", errno );
    }
  }
  else {
    // Block the child process for 1 second.
    sleep(1);

    // Now, release the semaphore.
    ops[2].sem_num = 0;
    ops[2].sem_op = -1; // Subtract 1 from semval.
    ops[2].sem_flg = 0;

    if ( semop( semid, ops + 2, 1 ) == 0 ) {
    }
    else {
      printf( "[parent] semop 2 got an error: %d\n", errno );
    }

    int child_status;
    wait( &child_status );
  }
}
