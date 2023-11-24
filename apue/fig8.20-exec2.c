#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void err_sys(const char *msg) {
  perror(msg); // Use perror to print the error message along with the system
               // message.
  exit(EXIT_FAILURE); // Exit the program with a failure status.
}

int main(void) {
  pid_t pid;

  // Fork a new process
  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) { // This is the child process
    // Replace the child process with the testinterp program
    if (execl("/Users/jim/Desktop/碩一上/進階 UNIX "
              "程式設計/Advanced-UNIX-Programming_team18/apue/testinterp",
              "testinterp", "myarg1", "MY ARG2", (char *)0) < 0) {
      err_sys("execl error");
    }
  }

  // This is the parent process, waiting for the child to finish
  if (waitpid(pid, NULL, 0) < 0) {
    err_sys("waitpid error");
  }

  exit(0); // Exit with a success status
}
