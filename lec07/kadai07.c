#include <stdio.h>
#include <math.h>
#define MAX 1000000

unsigned int xorshift();
int random_integer(int);

int main()
{
  int sex[2], day[2];
  int girlsunn, andgirln;
  int i, j;
  girlsunn = andgirln = 0;

  for (i = 0; i < MAX; i++) {
    for (j = 0; j < 2; j++) {
      sex[j] = random_integer(2);
      day[j] = random_integer(7);
    }
    if ((sex[0] == 1 && day[0] == 0) || (sex[1] == 1 && day[1] == 0)) {
      girlsunn++;
      if (sex[0] == 1 && sex[1] == 1) {
        andgirln++;
      }
    }
  }
  printf("%lf\n", (double)andgirln / (double)girlsunn);
  return 0;
}
unsigned int xorshift() 
{
  static unsigned int x = 1;
  static unsigned int y = 2;
  static unsigned int z = 3;
  static unsigned int w = 4;
  unsigned int t;
  t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  return w = (w^ (w>>19)) ^ (t ^ (t >> 8));
}

int random_integer(int m) 
{
  return xorshift() % m;
}

