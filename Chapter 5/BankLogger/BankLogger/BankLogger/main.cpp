#include <cstdio>
#include <stdexcept>

struct Logger {
    virtual ~Logger() = default;
    virtual void logTransfer(long from, long to, double amount) = 0;
};

struct FileLogger : Logger {
    void logTransfer(long from, long to, double amount) {
        //...
        printf("[file] %ld,%ld,%f\n", from, to, amount);
    }
};

struct ConsoleLogger : Logger {
    void logTransfer(long from, long to, double amount) override {
        printf("[cons] %ld -> %ld: %f\n", from, to, amount);
    }
};

enum class LoggerType {
    Console,
    File
};

class Bank {
    LoggerType type;
    ConsoleLogger consoleLogger;
    FileLogger fileLogger;

public:
    Bank() : type { LoggerType::Console } { }

    void setLogger(LoggerType newType) {
        type = newType;
    }

    void makeTransfer(long from, long to, double amount) {
        //...
        switch (type) {
            case LoggerType::Console: {
                consoleLogger.logTransfer(from, to, amount);
                break;
            }
            case LoggerType::File: {
                fileLogger.logTransfer(from, to, amount);
                break;
            } default: {
                throw std::logic_error("Unknown Logger type encountered.");
            }
        }
    }
};

int main() {
    Bank bank;
    bank.makeTransfer(1000, 2000, 49.95);
    bank.makeTransfer(2000, 4000, 20.00);
    bank.setLogger(LoggerType::File);
    bank.makeTransfer(3000, 2000, 75.00);

    return 0;
}