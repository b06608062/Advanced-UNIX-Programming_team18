#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int count = 0;
int flag = 0;

void pthread_barrier_wait_() {
  pthread_mutex_lock(&mutex);
  count++;
  if (count == NUM_THREADS) {
    flag = 1;
    pthread_cond_broadcast(&cond);
  } else {
    while (!flag) {
      pthread_cond_wait(&cond, &mutex);
    }
  }
  pthread_mutex_unlock(&mutex);
}

void *do_work(void *arg) {
  pthread_barrier_wait_();
  pthread_t thread_id = pthread_self();
  printf("Thread %lu running\n", (unsigned long)thread_id);

  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t threads[NUM_THREADS];

  for (int i = 0; i < NUM_THREADS; i++) {
    printf("Starting thread %d\n", i);
    if (pthread_create(&threads[i], NULL, do_work, NULL) != 0) {
      perror("pthread_create error");
      exit(1);
    }
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);

  return 0;
}