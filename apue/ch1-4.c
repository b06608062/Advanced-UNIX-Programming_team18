#include <math.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  double calendar_time;
  calendar_time = pow(2, 31) - 1;
  printf("%f\n", calendar_time / (60 * 60 * 24 * 365));

  return 0;
}
