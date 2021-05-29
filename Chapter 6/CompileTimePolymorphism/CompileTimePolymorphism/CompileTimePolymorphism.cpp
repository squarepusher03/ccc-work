#include <cstdio>
#include <iostream>
#include <stdexcept>

template<typename X, typename Y, typename Z>
class MyTemplateClass {
    Z* member;

public:
    X foo(Y&) { }
};

template<typename X, typename Y, typename Z>
X myTemplateFunction(Y& arg1, const Z* arg2) { }

void carbonThaw(const int& encasedSolo) {
    auto& hibernationSickSolo = const_cast<int&>(encasedSolo); // casting from const to normal
    hibernationSickSolo++;
}

short incrementAsShort(void* target) {
    auto asShort = static_cast<short*>(target);
    *asShort += 1;
    return *asShort;
}

struct Parent
{
    Parent() {
        num = 0;
    }

    int getNum() {
        return num;
    }

    virtual void addOne() = 0;

protected:
    int num;
};

struct Child1 : public Parent
{
    void addOne() {
        num++;
    }
};

struct Child2 : public Parent
{
    void addOne() {
        num -= 1;
    }
};

int incrementNum(void* target) {
    auto instance = static_cast<Parent*>(target);
    instance->addOne();
    return instance->getNum();
}

template <typename To, typename From>
To narrow_cast(From value) {
    const auto converted = static_cast<To>(value);
    const auto backwards = static_cast<From>(converted);
    if (value != backwards) throw std::runtime_error{ "Narrowing conversion." };
    return converted;
}

int main()
{
    int x{ 496 };
    const auto xShort = narrow_cast<short>(x);
    std::cout << "xShort: " << xShort << std::endl;
    try {
        int y{ 142857 };
        const auto yShort = narrow_cast<short>(y);
        std::cout << "yShort: " << yShort << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Runtime Error: " << e.what() << std::endl;
    }
    return 0;
}