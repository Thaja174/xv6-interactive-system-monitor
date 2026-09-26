#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int
main(void)
{
  int fd[10];
  int p[2];
  int i;
  int opened = 0;
  int d;

  for(i = 0; i < 10; i++)
    fd[i] = -1;

  printf("Resource Guard test\n");
  printf("Maximum open file descriptors: 8\n");

  /* Test open() quota. */
  for(i = 0; i < 10; i++){
    fd[i] = open("README", O_RDONLY);

    if(fd[i] < 0){
      printf("open %d: FAILED (quota reached)\n", i + 1);
      break;
    }

    opened++;
    printf("open %d: SUCCESS (fd=%d)\n", i + 1, fd[i]);
  }

  /* Test dup() while quota is full. */
  d = dup(fd[0]);
  if(d < 0)
    printf("dup at quota: FAILED (quota enforced)\n");
  else{
    printf("dup at quota: UNEXPECTED SUCCESS (fd=%d)\n", d);
    close(d);
  }

  /* Free one descriptor and verify reuse. */
  if(opened > 0){
    close(fd[0]);
    fd[0] = -1;

    fd[0] = open("README", O_RDONLY);

    if(fd[0] >= 0)
      printf("after close: SUCCESS (fd=%d)\n", fd[0]);
    else
      printf("after close: FAILED\n");
  }

  /* Fill the quota again, then test pipe(). */
  if(opened > 0){
    close(fd[0]);
    fd[0] = -1;

    for(i = 0; i < 10; i++){
      if(fd[i] >= 0){
        close(fd[i]);
        fd[i] = -1;
      }
    }

    for(i = 0; i < 5; i++){
      fd[i] = open("README", O_RDONLY);
    }

    if(pipe(p) < 0)
      printf("pipe at quota: FAILED (quota enforced)\n");
    else{
      printf("pipe at quota: UNEXPECTED SUCCESS\n");
      close(p[0]);
      close(p[1]);
    }
  }

  for(i = 0; i < 10; i++){
    if(fd[i] >= 0)
      close(fd[i]);
  }

  exit(0);
}
