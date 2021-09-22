#include <cstdio>
#include <stdexcept>

struct Groucho {
    void forget(int x) {
        if (x == 0xFACE) {
            throw std::runtime_error( "I'd be glad to make an exception." );
        }
        printf("Forgot 0x%x\n", x);
    }
};

int main()
{
    Groucho groucho;
    try {
        groucho.forget(0xB4D);
        groucho.forget(0xFACE);
        groucho.forget(0xC0FFEE);
    }
    catch (const std::runtime_error& e) {
        printf("Exception caught with message: %s\n", e.what()); // .what() returns the message thrown.
    }
}