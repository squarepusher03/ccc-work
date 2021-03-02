#pragma warning(disable : 4996)

#include <cstdio>
#include <cstring>
#include <stdexcept>

class SimpleString {
    size_t max_size;
    size_t length;
    char* buffer;

public:
    SimpleString(const SimpleString& other) : max_size{ other.max_size }, buffer{ new char[other.max_size] }, length{ other.length } { // Creates copy of passed SimpleString instance
        std::strncpy(buffer, other.buffer, max_size);
    };
    
    SimpleString& operator=(const SimpleString& other) { // copy assignment
        if (this == &other) return *this; // if this is passed, just return itself
        delete[] buffer; // deletes the old buffer pointer to prevent double frees.
        const auto new_buffer = new char[other.max_size];
        buffer = new_buffer;
        length = other.length;
        max_size = other.max_size;
        std::strncpy(buffer, other.buffer, max_size);
        return *this;
    }

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

    bool append_line(const char* new_line) {
        const auto x_len = strlen(new_line);
        if (x_len + length + 2 > max_size) return false; // checks if it can fit the new line, newline, and a null character
        strncpy(buffer + length, new_line, max_size - length); // adds the new_line to the end of the buffer
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
    //SimpleString string{ 115 };
    //string.append_line("Remember remember, ");
    //string.append_line("The fifth of November,");
    //string.print("V");
    //string.append_line("Of gunpowder, treason, and plot, ");
    //string.append_line("I know of no reason, ");
    //string.print("A");
    //if (!string.append_line("the Gunpowder Treason ")) {
    //    printf("String was not big enough to append.");
    //}
    //string.append_line("should ever be forgot.");

    //SimpleStringOwner x{ "x" };
    //printf("x is alive\n");

    //SimpleStringOwner a{ "a" };
    //    fn_b();
    //    SimpleStringOwner d{ "d" };

    //SimpleString a{ 20 };
    //a.append_line("Hello");
    //a.print("A");
    //SimpleString a_copy{ a };
    //a_copy.print("B");
    //a.append_line("World");
    //a_copy.append_line("People");
    //a.print("C");
    //a_copy.print("D");

    try {
        SimpleString a{ 50 };
        a.append_line("We apologize for the");
        SimpleString b{ 50 };
        b.append_line("Last message");
        a.print("a");
        b.print("b");
        b = a;
        a.print("a");
        b.print("b");
    }
    catch (const std::exception& e) {
        printf("Exception: %s", e.what());
    }
}