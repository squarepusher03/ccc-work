#include <cstdio>

struct College {
    char name[256];
};

void print_name(College* colleges, size_t n_colleges) {
    for (size_t index{ 0 }; index < n_colleges; index++) {
        printf("%s College\n", colleges[index].name);
    }
}

int main()
{
    int a{};
    printf("a: %d\n", a);
    int* a_1{ &a };
    printf("&a: %p\n", a_1);

    *a_1 = { 1 };
    printf("*a_1: %d\n", *a_1);

    College best_colleges[] = { "Magdalen", "Nuffield", "Kellogg" };
    // param: obj type ptr and length, args: array with obj type and length
    print_name(best_colleges, sizeof(best_colleges) / sizeof(College));

    char lower[]{ "abc?e" };
    char upper[]{ "ABC?E" };
    char *upper_ptr{ upper }; // equivalent to &upper[0]

    lower[3] = 'd';         // abcde
    *(upper_ptr + 3) = 'D'; // ABCDE

    char letter_d{ lower[3] };
    char letter_D{ upper_ptr[3] };

    printf("lower: %s\nupper: %s\n", lower, upper);

    int original{ 100 };
    int& original_ref{ original };
    printf("Original: %d\nReference: %d\n", original, original_ref);

    int new_value{ 200 };
    original_ref = { new_value }; // assigns new value to what original_ref references (a.k.a. original)
    printf("Original: %d\nNew Value: %d\nReference: %d", original, new_value, original_ref);

    return 0;
}