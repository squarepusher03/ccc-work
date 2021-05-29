#include <iostream>
#include <stdexcept>

template <typename T>
T mean(const T* values, size_t length) {
    T result{};
    for (size_t i{}; i < length; i++) {
        result += values[i];
    }
    return result / length;
}

int main()
{
    const double x[] { 1.2, 8.9, 6.5, 4.2 };
    std::cout << mean(x, (sizeof(x) / sizeof(double))) << std::endl;
}