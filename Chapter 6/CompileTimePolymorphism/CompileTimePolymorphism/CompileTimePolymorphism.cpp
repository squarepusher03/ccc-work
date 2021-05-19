#include <cstdio>

template<typename X, typename Y, typename Z>
class MyTemplateClass {
    Z* member;

public:
    X foo(&Y) { }
};

template<typename X, typename Y, typename Z>
X myTemplateFunction(Y& arg1, const Z* arg2) { }

int main()
{

    return 0;
}