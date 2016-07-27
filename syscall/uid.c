#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <errno.h>

int main( int argc, char** argv ) {

#ifdef linux
  return 0;
#endif

  uid_t uid = getuid();
  printf( "uid: %u\n", uid );

  uid_t euid = geteuid();
  printf( "euid: %u\n", euid );

  if (uid == euid) {
    struct passwd* pw = getpwuid(uid);
    if ( pw ) {
      printf( "username: %s\n", pw->pw_name );
    }
  }

  if ( setuid(0) == -1 ) {
    switch (errno) {
    case EPERM:
      printf( "Cannot set uid to 0: permission denied.\n" );
      break;
    default:
      printf( "Cannot set uid to 0 with errno: %d\n", errno );
      break;
    }
  }

  uid = getuid();
  printf( "uid: %u\n", uid );

  euid = geteuid();
  printf( "euid: %u\n", euid );

  gid_t gid = getgid();
  printf( "gid: %u\n", gid );

  gid_t egid = getegid();
  printf( "egid: %u\n", egid );

  if (gid == egid) {
    struct group* gr = getgrgid(gid);
    if ( gr ) {
      printf( "groupname: %s\n", gr->gr_name );
    }
  }

  if ( setgid(0) == -1 ) {
    switch (errno) {
    case EPERM:
      printf( "Cannot set gid to 0: permission denied.\n" );
      break;
    default:
      printf( "Cannot set gid to 0 with errno: %d\n", errno );
      break;
    }
  }

  gid = getgid();
  printf( "gid: %u\n", gid );

  egid = getegid();
  printf( "egid: %u\n", egid );
}
