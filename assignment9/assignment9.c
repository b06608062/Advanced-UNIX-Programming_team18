#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5
static pthread_barrier_t barrier;

void *do_work(void *arg) {
  pthread_barrier_wait(&barrier);
  pthread_t thread_id = pthread_self();
  printf("Thread %lu running\n", (unsigned long)thread_id);

  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t threads[NUM_THREADS];
  pthread_barrier_init(&barrier, NULL, NUM_THREADS);

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
  pthread_barrier_destroy(&barrier);

  return 0;
}