#include <iostream>
#include <stdexcept>
#include <limits>

struct CI {
    CI(unsigned int value) : value{ value } { }

    CI operator+(unsigned int other) const {
        CI result{ value + other };
        if (result.value < value) throw std::overflow_error{ "Overflow" };
        return result;
    }

    const unsigned int value;
};

int main()
{
    CI a{ 100 };
    auto b = a + 200;
    std::cout << "a + 200 = " << b.value << "\n";
    try {
        auto c = a + std::numeric_limits<unsigned int>::max();
    }
    catch (const std::overflow_error& e) {
        std::cout << "(a + max) Exception: " << e.what() << "\n";
    }
}