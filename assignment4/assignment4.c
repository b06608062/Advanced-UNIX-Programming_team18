#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]) {
  time_t raw_time;
  struct tm *time_info;
  char time_buffer[128];

  setenv("TZ", "Asia/Taipei", 1);
  tzset();

  time(&raw_time);
  time_info = localtime(&raw_time);

  strftime(time_buffer, 128, "%a %b %d %H:%M:%S %Z %Y", time_info);
  printf("%s\n", time_buffer);
}