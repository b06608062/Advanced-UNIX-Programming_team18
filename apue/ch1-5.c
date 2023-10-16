#include <math.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  double a = pow(2, 31) - 1;
  printf("%f\n", a / (100 * 60 * 60 * 24));
  return 0;
}