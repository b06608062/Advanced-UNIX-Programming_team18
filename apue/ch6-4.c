#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  printf("Size of time_t: %lu bytes\n", sizeof(time_t));

  setenv("TZ", "UTC", 1);
  tzset(); // 通知系統讀取和使用新的時區設置

  time_t init_time = 0;
  time_t short_int_max_time = pow(2, 31) - 1;
  time_t short_int_min_time = -pow(2, 31);

  // Convert and print the times
  printf("init_time: %s", ctime(&init_time));
  printf("short_int_min_time: %s", ctime(&short_int_min_time));
  printf("short_int_max_time: %s", ctime(&short_int_max_time));

  return 0;
}
