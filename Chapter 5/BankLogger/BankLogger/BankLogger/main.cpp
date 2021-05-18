#include <cstdio>
#include <stdexcept>

struct Logger {
    virtual ~Logger() = default;
    virtual void logTransfer(long from, long to, double amount) = 0;
};

struct FileLogger : Logger {
    void logTransfer(long from, long to, double amount) override {
        printf("[file] %ld,%ld,%f\n", from, to, amount);
    }
};

struct ConsoleLogger : Logger {
    void logTransfer(long from, long to, double amount) override {
        printf("[cons] %ld -> %ld: %f\n", from, to, amount);
    }
};

class Bank {
    Logger *logger;

public:
    void setLogger(Logger* logger) {
        this->logger = logger;
    }

    void makeTransfer(long from, long to, double amount) {
        if (logger) logger->logTransfer(from, to, amount);
    }
};

int main() {
    ConsoleLogger consoleLogger;
    FileLogger fileLogger;
    Bank bank;
    bank.setLogger(&consoleLogger);
    bank.makeTransfer(1000, 2000, 49.95);
    bank.setLogger(&fileLogger);
    bank.makeTransfer(2000, 4000, 20.00);

    return 0;
}