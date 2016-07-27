#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void fork_wait() {
  int child_status;
  pid_t child_pid;

  if (fork() == 0) {
    pid_t cur_pid = getpid();
    printf("Process %d: hello from child\n", cur_pid);
  }
  else {
    pid_t cur_pid = getpid();
    child_pid = wait( &child_status );
    printf("Process %d: child %d has terminated.\n",
           cur_pid,
           child_pid);
  }

  pid_t cur_pid = getpid();
  printf("Process %d: Bye\n", cur_pid);
}

int main( int argc, char** argv ) {
  fork_wait();
  exit(0);
}
