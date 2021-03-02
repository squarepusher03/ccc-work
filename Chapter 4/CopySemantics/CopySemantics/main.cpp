#include <cstdio>

int add_one_to(int x) noexcept {
    return ++x;
}

struct Point {
    int x, y;
};

Point make_transpose(Point p) {
    int tmp = p.x;
    p.x = p.y;
    p.y = tmp;
    return p;
}

void print_point(Point p) {
    printf("(%d, %d)\n", p.x, p.y);
}

int main() {
    Point p;
    p.x = 1;
    p.y = 2;
    print_point(p);
    print_point(make_transpose(p));
    print_point(p);

    return 0;
}