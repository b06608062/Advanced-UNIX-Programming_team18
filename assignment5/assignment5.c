#include <stdio.h>

int *f1(int *p2Val) { return p2Val; }

int main(int argc, char const *argv[]) {
  int val = 5;
  // printf("Value %d is at %p\n", val, &val);

  int *p2Val = f1(&val);
  printf("Value %d is at %p\n", *p2Val, p2Val);

  return 0;
}
