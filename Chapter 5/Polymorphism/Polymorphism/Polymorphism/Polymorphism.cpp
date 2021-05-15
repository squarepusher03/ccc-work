#include <cstdio>

class BaseClass { 
    const char* holistic_detective = "Dirk Gently";

public:
    virtual ~BaseClass() = default;
    virtual int x() const { return 1; }
    virtual const char* hello() const = 0;
    const char* member = "gold";
};

struct DerivedClass : BaseClass { 
    int y = 0;
    int x() const override { return 2; }
    const char* hello() const override { return "hello"; }
    DerivedClass() { printf("DerivedClass()\n"); }
    ~DerivedClass() override { printf("~DerivedClass()\n"); }

private:
    int z = 1;
};

int main()
{
    //BaseClass base; 
    DerivedClass derived;
    BaseClass* ref = new DerivedClass();
    //printf("x = %d\n", base.x());
    printf("y = %d\n", derived.x());
    printf("z = %d\n", ref->x());
    printf("%s member.\n", derived.member);
    delete ref;
}