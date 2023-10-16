#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  if (open("1GB.bin", O_RDWR) < 0)
    printf("open error");
  if (unlink("1GB.bin") < 0)
    printf("unlink error");
  printf("file unlinked\n");
  sleep(15);
  printf("done\n");
  exit(0);
}