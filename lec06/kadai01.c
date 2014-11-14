#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void stats(int, double *, double *, double *);

int main(int argc, char *argv[]) 
{
    int num = argc - 1;
    double data[num];
    double ave, var;
    int i;
    
    for (i = 0; i < num; i++){
        data[i] = atof(argv[i+1]);
        ave += data[i];
    }
    stats(num, data, &ave, &var);

    printf("average: %lf, variance: %lf\n", ave, var);
    
    return 0;
}

/*  要素数Nの数値列dataをもらい、平均ave, 分散var を返す */
void stats(int N, double data[], double *ave, double *var)
{
    int i;
    
    *ave = *var = 0;
    for (i = 0; i < N; i++){
        *ave += data[i];
    }
    *ave /= N;
    for (i = 0; i < N; i++) {
        *var += pow(data[i]-*ave, 2);
    }
    *var /= N;
    return;
}



