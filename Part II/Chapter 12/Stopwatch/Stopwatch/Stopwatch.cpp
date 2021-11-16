#include <iostream>
#include <chrono>
#include <thread>
#include "Stopwatch.h"
using namespace std;
using namespace literals::chrono_literals;

Stopwatch::Stopwatch(chrono::nanoseconds& result) : result{ result }, start{ chrono::high_resolution_clock::now() } {}
Stopwatch::~Stopwatch() {
    result = chrono::high_resolution_clock::now() - start;
}

//int main() {
//    const size_t n = 1'000'000;
//    chrono::nanoseconds elapsed;
//    {
//        Stopwatch stopwatch{ elapsed };
//        volatile double result{ 1.23e45 };
//        for (double i = 1; i < n; i++) {
//            result /= i;
//        }
//    }
//    auto time_per_division = elapsed.count() / double{ n };
//    cout << "Took " << time_per_division << "ns per division.\n";
//}