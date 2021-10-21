#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <deque>
using namespace std;

//template <typename T>
//istream& operator>>(istream& s, deque<T>& t) {
//    T element;
//    while (s >> element) {
//        t.emplace_back(move(element));
//    }
//    return s;
//}
//
//int main() {
//    cout << "Enter numbers: ";
//    deque<int> numbers;
//    cin >> numbers;
//    int sum{};
//    cout << "Cumulative sum:\n";
//    for (const auto& element : numbers) {
//        sum += element;
//        cout << sum << '\n';
//    }
//}

//TEST_CASE("ostringstream produces strings with str") {
//    ostringstream ss;
//    ss << "By Grabthar's hammer, ";
//    ss << "by the suns of Worvan. ";
//    ss << "You shall be avenged.";
//    const auto lazarus = ss.str();
//
//    ss.str("I am Groot.");
//    const auto groot = ss.str();
//
//    REQUIRE(lazarus == "By Grabthar's hammer, by the suns of Worvan. You shall be avenged.");
//    REQUIRE(groot == "I am Groot.");
//}

//TEST_CASE("istringstream supports construction from a string") {
//    string numbers("1 2.23606 2");
//    istringstream ss{ numbers };
//    int a;
//    float b, c, d;
//    ss >> a;
//    ss >> b;
//    ss >> c;
//    REQUIRE(a == 1);
//    REQUIRE(b == Approx(2.23606));
//    REQUIRE(c == Approx(2));
//    REQUIRE_FALSE(ss >> d);
//}

//TEST_CASE("stringstream supports all string stream operations") {
//    stringstream ss;
//    ss << "Zed's DEAD";
//
//    string who;
//    ss >> who;
//    int what;
//    ss >> hex >> what;
//
//    REQUIRE(who == "Zed's");
//    REQUIRE(what == 0xdead);
//}

int main() {
    //ofstream ofile{ "lunchtime.txt", ios::out | ios::app };
    //ofile << "Time is an illusion.\n";
    //ofile << "Lunch time, " << 2 << "x so." << endl;

    ifstream ifile{ "numbers.txt" };
    auto maximum = numeric_limits<int>::min();
    int value;
    while (ifile >> value) {
        maximum = maximum < value ? value : maximum;
    }
    cout << "Maximum found was " << maximum << '\n';
}

// open rewritten to throw exceptions instead of silently failing
ifstream open(const char* path, ios_base::openmode mode = ios_base::in) {
    ifstream file{ path, mode };
    if (!file.is_open()) {
        string err{ "Unable to open file: " };
        err.append(path);
        throw runtime_error{ err };
    }
    file.exceptions(ifstream::badbit);
    return file;
}