#include <stdio.h>

double cf(int);

int main() {
    double e = 2 + 1.0 / cf(1);
    printf("%f\n", e);
    return 0;
}

double cf(int depth) { /*ここにコードを書く*/
    if (depth > 10) {
        return 1;
    }
    if ((depth % 3) == 2) {
        return 2 * (depth / 3 + 1) + 1.0 / cf(depth+1);
    } else {
        return 1.0 + 1.0 / cf(depth+1);
    }
    return 0;
}
