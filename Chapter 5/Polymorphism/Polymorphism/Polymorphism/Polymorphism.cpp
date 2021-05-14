#include <cstdio>

class BaseClass { 
    const char* holistic_detective = "Dirk Gently";

public:
    int x() const { return 1; }
    const char* member = "gold";
};
struct DerivedClass : BaseClass { };

int main()
{
    DerivedClass derived;
    printf("x = %d\n", derived.x());
    printf("%s member.\n", derived.member);
}