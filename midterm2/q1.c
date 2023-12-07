#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
  int count = 0;

  time_t raw_time;
  time(&raw_time);
  printf("Loop %d current seconds: %d\n", count, localtime(&raw_time)->tm_sec);

  while (1) {
    for (int i = 0; i < 6; i++) {
      sleep(10);
    }

    time(&raw_time);
    printf("Loop %d current seconds: %d\n", ++count,
           localtime(&raw_time)->tm_sec);

    if (count == 180)
      break;
  }

  return 0;
}
