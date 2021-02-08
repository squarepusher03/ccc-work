#include <cstdio>

class ClockOfTheLongNow {
    int year;
public:
    ClockOfTheLongNow() {
        year = 2021;
    }

    ClockOfTheLongNow(int year) {
        if (!set_year(year)) {
            this->year = 2021;
        }
    }

    void add_year() {
        year++;
    }
    
    bool set_year(int year) {
        if (year < 2021) return false;
        this->year = year;
        return true;
    }
    
    int get_year() const {
        return year;
    }
};

bool bIsLeapYear(const ClockOfTheLongNow& clock) {
    if (clock.get_year() % 4 > 0) return false;
    if (clock.get_year() % 100 > 0) return true;
    if (clock.get_year() % 400 > 0) return false;
    return true;
}

void add_year(ClockOfTheLongNow& clock) {
    clock.set_year(clock.get_year() + 1);
}

struct Avout {
    Avout(const char* name, long year_of_apert) : name{ name }, apert{ year_of_apert } { }
    void announce() const {
        printf("My name is %s and my next apert is %d.\n", name, apert.get_year());
    }
    const char* name = "Erasmas";
    ClockOfTheLongNow apert;
};

int main()
{
    Avout raz{ "Erasmas", 3010 };
    Avout jad{ "Jad", 4000 };
    raz.announce();
    jad.announce();
    
    return 0;
}
