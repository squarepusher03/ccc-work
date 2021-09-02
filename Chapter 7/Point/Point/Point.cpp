#include <iostream>
#include <new>

struct Point {
    Point() : x{}, y{}, z{} {
        std::cout << "Point at " << this << " constructed.\n";
    }
    ~Point() {
        std::cout << "Point at " << this << " deconstructed.\n";
    }

    double x, y, z;
};

int main()
{
    const auto pointSize = sizeof(Point);
    std::byte data[3 * pointSize];
    std::cout << "Data starts at " << data << ".\n";
    auto point1 = new(&data[0 * pointSize]) Point{};
    auto point2 = new(&data[1 * pointSize]) Point{};
    auto point3 = new(&data[2 * pointSize]) Point{};
    point1->~Point();
    point2->~Point();
    point3->~Point();
}