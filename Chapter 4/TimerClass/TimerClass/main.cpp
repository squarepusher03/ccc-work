#include <iostream>
#include <string.h>
#include <stdexcept>
#include <utility>
#include <windows.h>

struct TimerClass {
    unsigned long long timestamp;
    const size_t SIZE = 51;
    char* name = new char[SIZE];
    bool movedFrom = false;

    bool nameTimer(const char* name) {
        const auto nameLength = strlen(name);
        if (nameLength + 1 > SIZE) return false;
        snprintf(this->name, sizeof(this->name), "%s", name);
        this->name[nameLength] = '\0';
        return true;
    }

public:
    TimerClass(const char* name) noexcept {
        nameTimer(name);
        timestamp = GetTickCount64();
    }

    ~TimerClass() noexcept {
        if (!movedFrom) {
            std::cout << name << " : " << GetTickCount64() - timestamp << "\n";
        }
    }

    TimerClass(const TimerClass& other) : timestamp{ other.timestamp } {
        nameTimer(other.name);
    }

    TimerClass& operator=(const TimerClass& other) {
        if (this == &other) return *this;
        delete[] name;
        timestamp = other.timestamp;
        nameTimer(other.name);
    }

    TimerClass(TimerClass&& other) noexcept : timestamp{ other.timestamp } {
        other.movedFrom = true;
        other.timestamp = 0;
        nameTimer(other.name);
        other.name = nullptr;
    }

    TimerClass& operator=(TimerClass&& other) noexcept {
        other.movedFrom = true;
        if (this == &other) return *this;
        timestamp = other.timestamp;
        other.timestamp = 0;
        nameTimer(other.name);
        other.name = nullptr;
        return *this;
    }
};

int main() {
    
}