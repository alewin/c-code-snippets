#include <unistd.h>    /* getpid */
#include <signal.h>    /* sigaction, kill */
#include <stdio.h>
#include <errno.h>

void new_sig_handler( int signum ) {
  printf( "[sig] new_sig_handler called: " );

  switch( signum ) {
  case SIGINT:
    printf( "SIGINT" );
    break;
  default:
    printf( "%d", signum );
    break;
  }

  printf( "\n" );
}

int main( int argc, char** argv ) {
  struct sigaction new_action, old_action;
  new_action.sa_handler = new_sig_handler;

  /*
    int sigaction(int signum, const struct sigaction *act,
                  struct sigaction *oldact);
  */
  sigaction( SIGINT, &new_action, &old_action );

  int pid = getpid();

  printf( "[sig] pid = %d\n", pid );

  kill(pid, SIGINT);
}
