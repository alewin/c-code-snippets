#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

enum {
  MSG_BUF_SIZE = 128,
};

typedef struct msg_buf {
  long mtype;
  char mtext[MSG_BUF_SIZE];
} msg_buf;

int main (int argc, char** argv) {

  int child_status;

  key_t msqid = msgget( IPC_PRIVATE,
                        IPC_CREAT | IPC_EXCL | 0600 /* permissions */ );
  msg_buf msg;
  msg.mtype = 1;
  sprintf(msg.mtext, "%s", "Hello, world!");

  if ( msqid == -1 ) {
    printf( "Failed to create msg queue with errno: %d\n", errno );
    return 1;
  }

  if ( fork() == 0 ) {
    printf( "Child forked.\n" );

    if ( msgsnd(msqid, &msg, sizeof(msg.mtext), 0) == -1 ) {
      printf( "Failed to send msg: %s with errno: %d\n", msg.mtext, errno );
      return 1;
    }
    else {
      printf( "Message: %s sent.\n", msg.mtext );
    }
  }
  else {
    if ( msgrcv(msqid, &msg, sizeof(msg.mtext), 0, 0) == -1 ) {
      printf( "Failed to receive msg with errno: %d\n", errno );
      return 1;
    }
    else {
      printf( "Message: %s received.\n", msg.mtext );
    }

    // Wait for the child to terminate.
    wait( &child_status );
    printf( "Child has terminated.\n" );

    if ( msgctl(msqid, IPC_RMID, NULL) == -1 ) {
      printf( "Failed to close msg queue with errno: %d\n", errno );
      return 1;
    }

    printf("Parent now terminates.\n");
  }
}
