#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  pid_t pid;
  char cmd[50] = {0};

  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  }

  if (pid == 0) {
    exit(0);
  }

  if (pid > 0) {
    printf("The child PID is %d\n", pid);
    snprintf(cmd, sizeof(cmd), "ps -p %d", pid);
    sleep(2);
    system(cmd);
    exit(0);
  }
}
