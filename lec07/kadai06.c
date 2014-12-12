#include <stdio.h>
#include <math.h>
#define MAX 100000

int random_integer(int);
int random_ex_integer(int m, int ex);

int main()
{
  int car, open, select, canopen;
  int i;
  double prob = 0;

  for (i = 0; i < MAX; i++) {
    canopen = 0;
    car = random_integer(3);
    select = random_integer(3);
    if (car != select) {
      while(canopen != car && canopen != select) {
        canopen++;
      }
    }
      
    if (car == select) {
      open = random_ex_integer(2,car);
    } else {
      open = canopen;
    }

    if (car == select) {
      prob++;
    }
  }
  prob /= MAX;

  printf("変えた場合 %lf\n変えない場合 %lf\n", 1- prob, prob);
  
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

int random_ex_integer(int m, int ex)
{
  int ret = xorshift() % (m-1);
  if (ret >= ex) {
    ret++;
  }
  return ret;
}
