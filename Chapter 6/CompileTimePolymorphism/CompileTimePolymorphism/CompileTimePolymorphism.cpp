#include <cstdio>

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
    auto asShort = static_cast<short*>(target); // what does this even do
    *asShort += 1;
    return *asShort;
}

int main()
{

    return 0;
}