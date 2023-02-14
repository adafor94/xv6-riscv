#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int pipeline(int fdRead)
{
  int p;
  int n; 
  int fd[2];


  // Print read number or exit if file descriptor is closed
  if (read(fdRead, &p, sizeof(p)) > 0)
    printf("%d\n", p);
  else {
    close(fdRead);
    exit(0);
  }

  pipe(fd);

  // Child reads from newly created pipe 
  if (fork() == 0) {
    close(fdRead);
    close(fd[1]);
    pipeline(fd[0]);

  // Parent reads more data 
  } else {
    close(fd[0]);

    while (read(fdRead, &n, sizeof(n)) > 0) 
      // If n % p != 0 write to pipe connected to child
      if ((n % p) != 0) 
        write(fd[1], &n, sizeof(n));
    
    // If reading is done
    // Close childs pipe and wait for the child to exit 
    close(fd[1]);
    wait(0); 
    close(fdRead);
  }

  return 0;
}

int
main(int argc, char *argv[])
{
  int fd[2];
  pipe(fd);

  // Write numbers to pipe
  for (int n=2; n < 36; n++) 
    write(fd[1], &n, sizeof(n));

  close(fd[1]);
  pipeline(fd[0]);
  exit(0);
}