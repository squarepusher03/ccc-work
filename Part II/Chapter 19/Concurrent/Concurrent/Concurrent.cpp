#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "Stopwatch.h"
#include <sstream>
#include <future>
#include <string>
#include <chrono>
#include <array>
#include <set>
using namespace std;
using namespace literals::string_literals;

/*
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
*/

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
    stringstream ss;
    ss << elapsed_ms << " ms: Factoring " << x << " ( ";
    for (auto factor : factors) ss << factor << " ";
    ss << ")\n";
    return ss.str();
}

array<unsigned long long, 6> numbers{
    9'699'690,
    179'426'549,
    1'000'000'007,
    4'294'967'291,
    4'294'967'296,
    1'307'674'368'000
};

int main() {
    chrono::nanoseconds elapsed_ns;
    {
        Stopwatch stopwatch{ elapsed_ns };
        vector<future<string>> factor_tasks;
        for (auto number : numbers) {
            factor_tasks.emplace_back(async(launch::async, factor_task, number));
        }
        for (auto& task : factor_tasks) {
            cout << task.get();
        }
    }
    const auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(elapsed_ns).count();
    cout << elapsed_ms << "ms: total program time." << endl;
}