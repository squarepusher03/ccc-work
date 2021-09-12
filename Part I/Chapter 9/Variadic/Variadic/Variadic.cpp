#include <iostream>
#include <cstdarg>

// Sums up the variadic args passed.
// Not type-safe and number of args required (size_t n below)
int sum(size_t n, ...) {
    va_list args;
    va_start(args, n);
    int result{};

    while (n--) {
        auto next_element = va_arg(args, int);
        result += next_element;
    }

    va_end(args);
    return result; 
}


// the stop condition of the recursive sum function below
// only returns x if it's the last argument
template <typename T>
constexpr T sum(T x) {
    return x;
}

// a recursive function to sum the arguments, last to first
// Much more type-safe and does not require length of args, but uses recursion (perhaps cringe, but optimized)
template <typename T, typename... Args>
constexpr T sum(T x, Args... args) {
    return x + sum(args...);
}

// uses a fold expression (... binary-operator parameter-pack)
// doesn't look like trash or use recursion so it's better than the others
template <typename... T>
constexpr auto sum(T... args) {
    return (... + args);
}

int main()
{
    std::cout << "The answer is " << sum(2, 4, 6, 8, 10, 12) << ".\n";
}
