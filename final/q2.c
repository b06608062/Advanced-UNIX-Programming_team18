#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void sleep_us(int microseconds) {
  struct timeval tv;
  tv.tv_sec = microseconds / 1000000;
  tv.tv_usec = microseconds % 1000000;
  select(0, NULL, NULL, NULL, &tv);
}
int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("error input\n");
    return 1;
  }
  int time_microseconds = atoi(argv[1]);
  struct timeval start, end;

  gettimeofday(&start, NULL);
  sleep_us(time_microseconds);
  gettimeofday(&end, NULL);

  long seconds = end.tv_sec - start.tv_sec;
  long sleep_usectime = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

  printf("Sleep time: %ld us\n", sleep_usectime);
  return 0;
}
