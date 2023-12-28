#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *T1(void *arg);
void *T2(void *arg);
void *T3(void *arg);

void sigint_handler(int signo);
void sigterm_handler(int signo);
void sigusr1_handler(int signo);

int main(int argc, char *argv[]) {
  pthread_t tid1, tid2, tid3;
  int err;

  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGINT);
  sigaddset(&set, SIGTERM);
  sigaddset(&set, SIGUSR1);
  pthread_sigmask(SIG_BLOCK, &set, NULL);

  if ((err = pthread_create(&tid1, NULL, &T1, NULL)) != 0) {
    perror("pthread_create error");
    exit(1);
  }

  if ((err = pthread_create(&tid2, NULL, &T2, NULL)) != 0) {
    perror("pthread_create error");
    exit(1);
  }

  if ((err = pthread_create(&tid3, NULL, &T3, NULL)) != 0) {
    perror("pthread_create error");
    exit(1);
  }

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);

  return 0;
}

void *T1(void *arg) {
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGINT);
  pthread_sigmask(SIG_UNBLOCK, &set, NULL);

  if (signal(SIGINT, sigint_handler) == SIG_ERR) {
    perror("signal error");
    exit(1);
  }

  pause();
}

void *T2(void *arg) {
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGTERM);
  pthread_sigmask(SIG_UNBLOCK, &set, NULL);

  if (signal(SIGTERM, sigterm_handler) == SIG_ERR) {
    perror("signal error");
    exit(1);
  }

  pause();
}

void *T3(void *arg) {
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGUSR1);
  pthread_sigmask(SIG_UNBLOCK, &set, NULL);

  if (signal(SIGUSR1, sigusr1_handler) == SIG_ERR) {
    perror("signal error");
    exit(1);
  }

  pause();
}

void sigint_handler(int signo) { printf("T1 handling SIGINT\n"); }

void sigterm_handler(int signo) { printf("T2 handling SIGTERM\n"); }

void sigusr1_handler(int signo) { printf("T3 handling SIGUSR1\n"); }