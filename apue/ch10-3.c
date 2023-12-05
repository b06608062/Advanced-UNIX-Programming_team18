#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

unsigned int sleep2(unsigned int);
static void sig_int(int);
static void sig_alrm(int);
static jmp_buf env_alrm;

static void sig_alrm(int signo) { longjmp(env_alrm, 1); }

unsigned int sleep2(unsigned int seconds) {
  if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
    return (seconds);
  }

  if (setjmp(env_alrm) == 0) {
    alarm(seconds); // start the timer
    // kill(getpid(), SIGINT);
    pause(); // next caught signal wakes us up
  }

  return (alarm(0)); // turn off timer, return unslept time
}

static void sig_int(int signo) {
  time_t start_time, current_time;

  printf("sig_int starting\n");
  start_time = time(NULL);

  do {
    current_time = time(NULL);
    // 這裡可以執行一些實際的工作或者忙等待
  } while (difftime(current_time, start_time) < 6.0);

  printf("sig_int finished\n");
}

int main(void) {
  unsigned int unslept;

  if (signal(SIGINT, sig_int) == SIG_ERR) {
    perror("signal(SIGINT) error");
  }

  unslept = sleep2(5);

  // pid_t pid = getpid();
  // kill(pid, SIGINT);

  printf("sleep2 returned: %u\n", unslept);

  exit(0);
}
