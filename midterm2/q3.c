#include <stdio.h>
#include <time.h>

int main() {
  time_t rawtime;
  struct tm *currenttime;
  char buffer[80];

  time(&rawtime);
  currenttime = localtime(&rawtime);

  strftime(buffer, sizeof(buffer), "%H:%M:%S, %A %B %d, %Y", currenttime);
  printf("%s\n", buffer);

  return 0;
}