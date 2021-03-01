#pragma warning(disable : 4996)

#include <cstdio>
#include <cstring>
#include <stdexcept>

class SimpleString {
    size_t max_size;
    size_t length;
    char* buffer;

public:
    SimpleString(size_t max_size) : max_size{ max_size }, length{} {
        if (max_size == 0) {
            throw std::runtime_error{ "Max size should be at least 1." };
        }
        buffer = new char[max_size];
        buffer[0] = 0;
    };

    ~SimpleString() noexcept {
        delete[] buffer;
    }

    void print(const char* tag) const noexcept {
        printf("%s: %s", tag, buffer);
    }

    bool append_line(const char* x) {
        const auto x_len = strlen(x);
        if (x_len + length + 2 > max_size) return false;
        strncpy(buffer + length, x, max_size - length);
        length += x_len;
        buffer[length++] = '\n';
        buffer[length] = 0;
        return true;
    }
};

class SimpleStringOwner {
    SimpleString string;

public:
    SimpleStringOwner(const char* x) : string{ 10 } {
        if (!string.append_line(x)) {
            throw std::runtime_error{ "Not enough memory!" };
        }
        string.print("Constructed");
    }

    ~SimpleStringOwner() noexcept {
        string.print("About to destroy");
    }
};

void fn_c() {
    SimpleStringOwner c{ "cccccccccc" };
}

void fn_b() {
    SimpleStringOwner b{ "b" };
    fn_c();
}

int main() {
    SimpleString string{ 115 };
    string.append_line("Remember remember, ");
    string.append_line("The fifth of November,");
    string.print("V");
    string.append_line("Of gunpowder, treason, and plot, ");
    string.append_line("I know of no reason, ");
    string.print("A");
    if (!string.append_line("the Gunpowder Treason ")) {
        printf("String was not big enough to append.");
    }
    string.append_line("should ever be forgot.");

    SimpleStringOwner x{ "x" };
    printf("x is alive\n");

    try {
        SimpleStringOwner a{ "a" };
        fn_b();
        SimpleStringOwner d{ "d" };
    }
    catch (const std::exception& e) {
        printf("Exception: %s", e.what());
    }
}