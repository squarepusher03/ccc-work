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
    const double aDouble[] { 1.0, 2.0, 3.0, 4.0 };
    std::cout << "double: " << mean(aDouble, 4) << std::endl;

    const float aFloat[] { 1.0f, 2.0f, 3.0f, 4.0f };
    std::cout << "float: " << mean(aFloat, 4) << std::endl;

    const size_t aSizeT[]{ 1, 2, 3, 4 };
    std::cout << "size_t: " << mean(aSizeT, 4) << std::endl;
}