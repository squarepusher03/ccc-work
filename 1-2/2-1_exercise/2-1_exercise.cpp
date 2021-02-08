#include <cstdio>

enum class Operation {
    Add,
    Subtract,
    Multiply,
    Divide
};

class Calculator {
    Operation op;

public:
    Calculator(Operation op) {
        this->op = { op };
    }

    Calculator() {
        op = Operation::Add;
    }

    Operation get_operator() const {
        return op;
    }

    void set_operator(Operation op) {
        this->op = { op };
    }

    int calculate(int a, int b) const {
        switch (op) {
            case Operation::Add: {
                return a + b;
            } break;
            case Operation::Subtract: {
                return a - b;
            } break;
            case Operation::Multiply: {
                return a * b;
            } break;
            case Operation::Divide: {
                return a / b;
            } break;
            default: {
                return 0;
            }
        }
    }
};

int main()
{
    Calculator* addition{ new Calculator{ Operation::Add } };
    Calculator* subtraction{ new Calculator{ Operation::Subtract } };
    Calculator* multiplication{ new Calculator{ Operation::Multiply } };
    Calculator* division{ new Calculator{ Operation::Divide } };
    int a{ 25 };
    int b{ 5 };

    printf("%d + %d = %d\n", a, b, addition->calculate(a, b));
    printf("%d - %d = %d\n", a, b, subtraction->calculate(a, b));
    printf("%d * %d = %d\n", a, b, multiplication->calculate(a, b));
    printf("%d / %d = %d\n", a, b, division->calculate(a, b));
    delete addition;
    delete subtraction;
    delete multiplication;
    delete division;

    Calculator* calculator{ new Calculator{ } };
    printf("Calc address: %p\nCalc return: %d\n", calculator, calculator->calculate(a, b));
    delete calculator;

    return 0;
}
