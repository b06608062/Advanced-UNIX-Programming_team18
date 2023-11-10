#include <fcntl.h>
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
    pid_t tpgid = tcgetpgrp(STDIN_FILENO);
    printf("Before setsid() Child PID: %d PGRP: %d TPGID: %d\n", getpid(),
           getpgrp(), tpgid);
    if (setsid() == -1) {
      perror("session error");
      exit(1);
    }
    tpgid = tcgetpgrp(STDIN_FILENO);
    printf("After setsid() Child PID: %d PGRP: %d TPGID: %d\n", getpid(),
           getpgrp(), tpgid);

    char cmd[50] = {0};
    snprintf(cmd, sizeof(cmd), "ps -o pid,pgid,tpgid,comm -p %d", getpid());
    system(cmd);
    return 1;
  } else {
    wait(NULL);
  }

  return 0;
}