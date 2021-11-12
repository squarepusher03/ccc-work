#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <sstream>
#include <future>
#include <string>
#include <chrono>
#include <set>
using namespace std;
using namespace literals::string_literals;

TEST_CASE("async returns valid future") {
    auto the_future = async([] { return "hello"s; });
    REQUIRE(the_future.valid());
}

TEST_CASE("future invalid by default") {
    future<bool> default_future;
    REQUIRE_FALSE(default_future.valid());
}

TEST_CASE("async returns the return value of the function obj") {
    auto the_future = async([] { return "hello"s; });
    REQUIRE(the_future.get() == "hello");
}

TEST_CASE("get may throw") {
    auto x = async([] { throw runtime_error{ "Something bad happened" }; });
    REQUIRE_THROWS_AS(x.get(), runtime_error);
}

TEST_CASE("wait_for indicates whether a task is ready") {
    auto sleepy = async(launch::async, [] { this_thread::sleep_for(100ms); });
    const auto not_ready_yet = sleepy.wait_for(25ms);
    REQUIRE(not_ready_yet == future_status::timeout);
    const auto totally_ready = sleepy.wait_for(100ms);
    REQUIRE(totally_ready == future_status::ready);
}

// from Chapter 12
class Stopwatch {
    chrono::nanoseconds& result;
    const chrono::time_point<chrono::high_resolution_clock> start;

public:
    Stopwatch(chrono::nanoseconds& result) : result{ result }, start{ chrono::high_resolution_clock::now() } {}
    ~Stopwatch() {
        result = chrono::high_resolution_clock::now() - start;
    }
};

template <typename T>
set<T> factorize(T x) {
    set<T> result{ 1 };
    for (T candidate{ 2 }; candidate <= x; candidate++) {
        if (x % candidate == 0) {
            result.insert(candidate);
            x /= candidate;
            candidate = 1;
        }
    }
    return result;
}

string factor_task(unsigned long long x) {
    chrono::nanoseconds elapsed_ns;
    set<unsigned long long> factors;
    {
        Stopwatch stopwatch{ elapsed_ns };
        factors = factorize(x);
    }
    const auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(elapsed_ns).count();
}