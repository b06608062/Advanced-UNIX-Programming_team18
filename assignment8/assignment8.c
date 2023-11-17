#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

char buf[32];
static volatile sig_atomic_t sigflag; /* set nonzero by sig handler */
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int signo) /* one signal handler for SIGUSR1 and SIGUSR2 */
{
  sigflag = 1;
}

static void TELL_WAIT(void) {
  if (signal(SIGUSR1, sig_usr) == SIG_ERR)
    perror("signal(SIGUSR1) error");

  if (signal(SIGUSR2, sig_usr) == SIG_ERR)
    perror("signal(SIGUSR2) error");

  sigemptyset(&zeromask);
  sigemptyset(&newmask);
  sigaddset(&newmask, SIGUSR1);
  sigaddset(&newmask, SIGUSR2);

  /* Block SIGUSR1 and SIGUSR2, and save current signal mask */
  if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    perror("SIG_BLOCK error");
}

static void TELL_PARENT(void) {
  kill(getppid(), SIGUSR2); /* tell parent we’re done */
}

static void WAIT_PARENT(void) {
  while (sigflag == 0)
    sigsuspend(&zeromask); /* and wait for parent */
  sigflag = 0;
  /* Reset signal mask to original value */
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    perror("SIG_SETMASK error");
}

static void TELL_CHILD(pid_t pid) {
  kill(pid, SIGUSR1); /* tell child we’re done */
}

static void WAIT_CHILD(void) {
  while (sigflag == 0)
    sigsuspend(&zeromask); /* and wait for child */
  sigflag = 0;
  /* Reset signal mask to original value */
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    perror("SIG_SETMASK error");
}

static int increment_counter(FILE *const file) { /* TODO */
  fseek(file, 0, SEEK_SET);
  if (fgets(buf, sizeof(buf), file) != NULL) {
    int value = atoi(buf);
    value++;
    sprintf(buf, "%d", value);
    fseek(file, 0, SEEK_SET);
    fputs(buf, file);
    fflush(file);
    return value;
  } else {
    perror("Error reading from file");
    return -1;
  }
}

int main(void) { /* TODO */
  FILE *file = fopen("./sample.txt", "w+");
  fputs("0\n", file);
  fflush(file);
  if (file == NULL) {
    perror("open error");
    exit(1);
  }
  TELL_WAIT();
  pid_t pid;
  if ((pid = fork()) < 0) {
    perror("fork error");
    exit(1);
  } else if (pid == 0) {
    for (int i = 0; i < 50; i++) {
      printf("Child incrementing, value: %d\n", increment_counter(file));
      TELL_PARENT();
      WAIT_PARENT();
    }
    exit(0);
  } else {
    for (int i = 0; i < 50; i++) {
      WAIT_CHILD();
      printf("Parent incrementing, value: %d\n", increment_counter(file));
      TELL_CHILD(pid);
    }
  }

  fclose(file);
  return 0;
}