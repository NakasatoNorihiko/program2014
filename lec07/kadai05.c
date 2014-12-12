#include <stdio.h>
#include <math.h>
#define N 100
#define MAX 100000

int random_integer(int);

int main()
{
  int i, j;
  int x[MAX];
  double p = 0;
  
  for (i = 0; i < MAX; i++){
    x[i] = 0;
  }

  for (i = 0; i < MAX; i++) {
    for (j = 0; j < N; j++) {
      if (random_integer(2)) {
        x[i]++;
      } else {
        x[i]--;
      }
    }
    if (x[i] >= 20) {
      p++;
    }
  }
  p /= MAX;
  printf("p = %lf\n", p);
  printf("帰無仮説「表と裏の出る確率は等しい」は");
  if (p > 0.05) {
    printf("棄却されない\n");
  } else {
    printf("棄却される\n");
  }
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
