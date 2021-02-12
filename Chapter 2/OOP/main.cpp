#include <cstdio>

int main() {
    float a{ 1 };
    float b{ 2 };
    double narrowed(a / b);

    printf("a = %f\nb = %f\nNarrowed = %lf", a, b, narrowed);

    return 0;
}