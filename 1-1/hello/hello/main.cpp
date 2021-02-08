#include <cstdio>

int sum(int x, int y) { return x + y; }

int absolute_value(int x) {
    if (x < 0) return x * -1;
    return x;
}

int main() {
    int num = 0;
    printf("The absolute value of %d is %d. The sum of itself and itself is %d.\n", num, absolute_value(num), sum(num, num));
}