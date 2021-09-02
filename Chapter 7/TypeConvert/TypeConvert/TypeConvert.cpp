#include <iostream>

class ReadInt {
    const int val;

public:
    ReadInt(int val) : val{val} { }
    explicit operator int() const {
        return val;
    }
    
    explicit operator double() const {
        return val / 1.0;
    }
};

struct Color {
    float h, s, v;
};

constexpr uint8_t max(uint8_t a, uint8_t b) {
    return a > b ? a : b;
}
constexpr uint8_t max(uint8_t a, uint8_t b, uint8_t c) {
    return max(max(a, b), max(a, c));
}
constexpr uint8_t min(uint8_t a, uint8_t b) {
    return a < b ? a : b;
}
constexpr uint8_t min(uint8_t a, uint8_t b, uint8_t c) {
    return min(min(a, b), min(a, c));
}
constexpr float modulo(float dividend, float divisor) {
    const auto quotient = dividend / divisor;
    return divisor * (quotient - static_cast<uint8_t>(quotient));
}

constexpr Color rgbToHsv(uint8_t r, uint8_t g, uint8_t b) {
    Color c{};
    const auto cMax = max(r, g, b);
    c.v = cMax / 255.0f;

    const auto cMin = min(r, g, b);
    const auto delta = c.v - cMin / 255.0f;
    c.s = cMax == 0 ? 0 : delta / c.v;

    if (cMax == cMin) {
        c.h = 0;
        return c;
    }
    if (cMax == r) {
        c.h = (g / 255.0f - b / 255.0f) / delta;
    }
    else if (cMax == g) {
        c.h = (b / 255.0f - r / 255.0f) / delta;
    }
    else if (cMax == b) {
        c.h = (r / 255.0f - g / 255.0f) / delta + 4.0f;
    }

    c.h *= 60.0f;
    c.h = c.h >= 0.0f ? c.h : c.h + 360.0f;
    c.h = modulo(c.h, 360.0f);
    return c;
}

int main() {
    //ReadInt x{ 4 };
    //std::cout << static_cast<int>(x) + 1 << "\n";
    //std::cout << static_cast<double>(x) + 1.0 << "\n";

    auto black = rgbToHsv(0, 0, 0);
    auto white = rgbToHsv(255, 255, 255);
    auto red = rgbToHsv(255, 0, 0);
    auto green = rgbToHsv(0, 255, 0);
    auto blue = rgbToHsv(0, 0, 255);
    Color list[] = { black, white, red, green, blue };
    
    for (int i = 0; i < sizeof(list) / sizeof(Color); i++) {
        std::cout << "HSV " << i << ": " << list[i].h;
        std::cout << ", " << list[i].s;
        std::cout << ", " << list[i].v << "\n";
    }

    return 0;
}