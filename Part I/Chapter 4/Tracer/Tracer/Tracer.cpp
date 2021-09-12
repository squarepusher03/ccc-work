#include <cstdio>

class Tracer {
    const char* const name;
public:
    Tracer(const char* name) : name{ name } {
        printf("%s is constructed.\n", name);
    }

    ~Tracer() {
        printf("%s is deconstructed.\n", name);
    }
};

// Static/thread-local variables can only be declared and defined in a class definition if they are const.
static Tracer t1{ "Static variable" };
thread_local Tracer t2{ "Thread-local variable" };

int main()
{
    const auto t2_ptr = &t2;
    printf("A\n");
    Tracer t3{ "Automatic variable" };
    printf("B\n");
    const auto* t4 = new Tracer{ "Dynamic variable" };
    printf("C\n");
    delete t4; // This is how to deconstruct a dynamic variable.
} // This is where all static, thread-local, and automatic variables deconstruct.
