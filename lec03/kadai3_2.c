/* エラトステネスのふるいの実装 */
/* 説明 */
/* 1. 2以外の素数は奇数のため、調べる対象を3以上の奇数とする(2は最初に素数としておく) */
/* 2. 検査数の上限をnの平方根までに限定 */
/* 3. 検査数を見つかった素数に限定 */
/* 1.だけ使うと余りを求める回数は498501->249001に減少する。これは調べるべき対象が約半分になったため。 */
/* 次に2.を用いると10482に減少する。検査数はおおよそで1.のときのnの平方根の逆数倍にであるから、n=100で10%,n=1000で3.1%程度。そのため減少率は1.に比べて大きくなったと考えられる。*/
/* 最後に3.を用いると2359に減少する。 */
/* ここでエラトステネスのふるいを用いる。エラトステネスのふるいはあまりを計算しないので、MAXを100000とした時の実行速度で比較する。上の方法では、コマンドを10回実行すると0.307sかかった。一方エラトステネス の篩では0.022sかかった。 */

#include <stdio.h>
#define MAX 1000000
#define PRIME 1
#define NOPRIME 0

int main() 
{
    int result[MAX]; /* result[i]がi+1が素数かを示す */
    int sqrmax = 1;
    int i, j, k;

    /* 検査数の最大は最大数の平方根 */
    while(sqrmax * sqrmax < MAX) {
        sqrmax++;
    }

    /* とりあえず2以上の整数は全て素数としておく */
    for(i = 1; i < MAX; i++) {
        result[i] = PRIME;
    }

    /* 検査数の分だけふるい落としていく */
    for (i = 2; i <= sqrmax; i++) {
      if (result[i-1] == PRIME) {
	for (j = i*2; j <= MAX; j += i) {
	  result[j-1] = NOPRIME;
	}
      }
    }

    /* for (i = 0; i < MAX; i++) { */
    /*     if (result[i] == PRIME) { */
    /*         printf("%d ", i+1); */
    /*     } */
    /* } */
    
    return 0;
}

