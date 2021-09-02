#include <iostream>

template <typename T>
class SUP {
    T* pointer;

public:
    SUP() { pointer = nullptr; };
    SUP(T* pointer) : pointer{ pointer } { };

    ~SUP() { delete pointer; };

    SUP(const SUP&) = delete;
    SUP& operator=(const SUP&) = delete;
    
    SUP(SUP&& other) noexcept : pointer{ other.pointer } { other.pointer = nullptr; }
    SUP& operator=(SUP&& other) noexcept {
        delete pointer;
        pointer = other.pointer;
        other.pointer = nullptr;
        return *this;
    }

    T* get() { return pointer; }
};

class Tracer {
    const char* const name;

public:
    Tracer(const char* name) : name{ name } {
        std::cout << name << " constructed." << std::endl;
    }

    ~Tracer() {
        std::cout << name << " destructed." << std::endl;
    }
};

void consumer(SUP<Tracer> consumerPtr) {
    std::cout << "(cons) consumerPtr: 0x" << consumerPtr.get() << std::endl;
}

template <typename T, typename... Arguments>
SUP<T> makeSUP(Arguments... arguments) {
    return SUP<T>{ new T{ arguments } };
}

int main()
{
    auto ptrA = SUP<Tracer>( new Tracer{ "ptrA" } );
    std::cout << "(main) ptrA: 0x" << ptrA.get() << std::endl;
    consumer(std::move(ptrA));
    std::cout << "(main) ptrA: 0x" << ptrA.get() << std::endl;

    return 0;
}