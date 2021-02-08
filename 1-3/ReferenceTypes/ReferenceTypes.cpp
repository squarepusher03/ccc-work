#include <cstdio>

struct College {
   char name[256];
};

void print_name(College* colleges, size_t n_colleges) {
   for (size_t index{ 0 }; index < n_colleges; index++) {
       printf("%s College\n", colleges[index].name);
   }
}

void read_from(const char* str, const size_t size, const int index) {
    if (((size_t)index < size) && (index >= 0)) {
        printf("%s\n", &str[index]);
    }
}

void write_to(char* str, const char new_char, const size_t size, const int index) {
    if (((size_t)index < size) && (index >= 0)) {
        str[index] = { new_char };
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

    char lower[]{ "abc?e" };
    char upper[]{ "ABC?E" };
    char *upper_ptr{ upper }; // equivalent to &upper[0]

    lower[3] = 'd';         // abcde
    *(upper_ptr + 3) = 'D'; // ABCDE

    char letter_d{ lower[3] };
    char letter_D{ upper_ptr[3] };

    printf("lower: %s\nupper: %s\n", lower, upper);

    // exercise 3-2
    size_t lower_size = sizeof(lower) / sizeof(char);
    size_t upper_size = sizeof(upper) / sizeof(char);
    read_from(lower, lower_size, 0); // prints whole strings
    read_from(upper, upper_size, 0);

    read_from(lower, lower_size, 3); // prints from arr[3]
    read_from(upper, upper_size, 3);

    read_from(lower, lower_size, 6); // doesn't print due to bounds check
    read_from(upper, upper_size, 6);
    
    write_to(lower, '$', lower_size, 2); // ab$de
    write_to(upper, '$', upper_size, 2); // AB$DE

    read_from(lower, lower_size, 0); // prints whole strings
    read_from(upper, upper_size, 0);

    write_to(lower, '$', lower_size, 6); // won't write, bounds checked
    lower_size = sizeof(lower) / sizeof(char);
    upper_size = sizeof(upper) / sizeof(char);

    read_from(lower, lower_size, 0); // prints whole strings
    read_from(upper, upper_size, 0);
    
    // end of exercise 3-2

    College best_colleges[] = { "Magdalen", "Nuffield", "Kellogg" };
    // param: obj type ptr and length, args: array with obj type and length
    print_name(best_colleges, sizeof(best_colleges) / sizeof(College));

    int original{ 100 };
    int& original_ref{ original };
    printf("Original: %d\nReference: %d\n", original, original_ref);

    int new_value{ 200 };
    original_ref = { new_value }; // assigns new value to what original_ref references (a.k.a. original)
    printf("Original: %d\nNew Value: %d\nReference: %d", original, new_value, original_ref);

    return 0;
}
