#include "my_math.h"

int power(int a, int n)
{
  int i;
  int power = 1;
  for (i = 0; i < n; i++) {
    power *= a;
  }
  return power;
}
