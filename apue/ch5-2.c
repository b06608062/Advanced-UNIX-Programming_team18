#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 4

int main(void) {
  char buf[MAXLINE];
  int count = 0;
  while (fgets(buf, MAXLINE, stdin) != NULL) {
    count++;
    if (fputs(buf, stdout) == EOF) {
      printf("output error\n");
    }
  }
  if (ferror(stdin))
    printf("input error\n");
  printf("%d lines read\n", count);
  exit(0);
}