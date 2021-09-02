#include <iostream>
#include <stdexcept>
#include <type_traits>

/*
template <typename To, typename From>
struct NarrowCaster {
    To cast(From value) const {
        const auto converted = static_cast<To>(value);
        const auto backwards = static_cast<From>(converted);
        if (value != backwards) throw std::runtime_error{ "Narrowing conversion." };
        return converted;
    }
};

template <typename From>
using short_caster = NarrowCaster<short, From>;

struct TextFile {
    bool success;
    const char* contents;
    size_t n_bytes;
};

TextFile read_text_file(const char* path) {
    const static char contents[]{ "Sometimes the goat is you." };
    return TextFile{
        true,
        contents,
        sizeof(contents)
    };
}
*/

template <typename T>
auto value_of(T x) {
    if constexpr (std::is_pointer<T>::value) {
        if (!x) throw std::runtime_error{ "Null pointer dereference." };
        return *x;
    }
    else {
        return x;
    }
}

int main()
{
    int x = 3;
    std::cout << value_of(x) << "\n";

    double y = 4.2;
    std::cout << value_of(y) << "\n";
    
    std::cout << value_of(&y) << "\n";

    int* z = nullptr;
    try {
        std::cout << value_of(z) << "\n";
    }
    catch (const std::runtime_error& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }

    /*
    try {
        const short_caster<int> caster;
        const auto cyclic_short = caster.cast(142857);
        std::cout << "cyclic_short: " << cyclic_short << "\n";
    }
    catch (const std::runtime_error& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
    
    const auto [success, contents, length] = read_text_file("README.txt");
    if (success) {
        std::cout << "Read " << length << " bytes: " << contents << "\n";
    }
    else {
        std::cout << "Failed to open README.txt\n";
    }
    */
}