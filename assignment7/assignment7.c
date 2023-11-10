#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid;

  if ((pid = fork()) == -1) {
    perror("fork error");
    exit(1);
  } else if (pid == 0) {
    printf("Child PID: %d PGRP: %d TPGID: %d\n", getpid(), getpgrp(),
           getsid(0));
    if (setsid() == -1) {
      perror("session error");
      exit(1);
    }
    printf("Child PID: %d PGRP: %d TPGID: %d\n", getpid(), getpgrp(),
           getsid(0));
    return 1;
  } else {
    wait(NULL);
  }

  return 0;
}
