#include <iostream>

class FibonacciIterator {
    int current{ 1 }, last{ 1 };

public:
    bool operator!=(int x) const {
        return x >= current;
    }

    FibonacciIterator& operator++() {
        const auto tmp = current;
        current += last;
        last = tmp;
        return *this;
    }

    int operator*() const {
        return current;
    }
};

class FibonacciRange {
    const int max;

public:
    explicit FibonacciRange(int max) : max{ max } { }
    FibonacciIterator begin() const {
        return FibonacciIterator{};
    }
    int end() const {
        return max;
    }
};

int main()
{
    for (const auto i : FibonacciRange{ 5000 }) {
        std::cout << i << " ";
    }
}